// Copyright Hollow Crown Studio. All Rights Reserved.

#include "Combat/HCCombatComponent.h"
#include "Combat/HCWeaponData.h"
#include "Stats/HCAttributeComponent.h"
#include "HollowCrown.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

UHCCombatComponent::UHCCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHCCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner())
	{
		Attributes = Owner->FindComponentByClass<UHCAttributeComponent>();
		if (Attributes)
		{
			Attributes->OnPoiseBroken.AddDynamic(this, &UHCCombatComponent::HandlePoiseBroken);
		}
	}
}

void UHCCombatComponent::EquipWeapon(UHCWeaponData* Weapon)
{
	EquippedWeapon = Weapon;
}

bool UHCCombatComponent::CanStartNewAction() const
{
	// Recovery is interruptible by the next combo input; windup/active/stagger are not.
	return AttackState == EHCAttackState::Idle
		|| AttackState == EHCAttackState::Recovery
		|| AttackState == EHCAttackState::Blocking;
}

void UHCCombatComponent::RequestAttack(EHCAttackType AttackType)
{
	if (!EquippedWeapon || !Attributes || !CanStartNewAction())
	{
		return;
	}

	const float Cost = GetStaminaCostForType(AttackType);
	if (!Attributes->TrySpendStamina(Cost))
	{
		return;
	}

	PendingAttackType = AttackType;
	HitActorsThisSwing.Reset();
	SetAttackState(EHCAttackState::Windup);

	// Play the montage; its AnimNotifies call OnAttackWindowOpen/Close and advance state.
	if (UAnimMontage* Montage = GetMontageForType(AttackType))
	{
		if (ACharacter* OwnerChar = Cast<ACharacter>(GetOwner()))
		{
			if (USkeletalMeshComponent* MeshComp = OwnerChar->GetMesh())
			{
				if (UAnimInstance* AnimInstance = MeshComp->GetAnimInstance())
				{
					AnimInstance->Montage_Play(Montage);
				}
			}
		}
	}
}

void UHCCombatComponent::StartBlock()
{
	if (!CanStartNewAction())
	{
		return;
	}

	BlockStartTime = GetWorld() ? GetWorld()->GetTimeSeconds() : 0.f;
	SetAttackState(EHCAttackState::Blocking);
}

void UHCCombatComponent::StopBlock()
{
	if (AttackState == EHCAttackState::Blocking || AttackState == EHCAttackState::Parrying)
	{
		SetAttackState(EHCAttackState::Idle);
	}
}

void UHCCombatComponent::RequestDodge()
{
	if (!Attributes || !CanStartNewAction())
	{
		return;
	}
	if (!Attributes->TrySpendStamina(DodgeStaminaCost))
	{
		return;
	}
	SetAttackState(EHCAttackState::Dodging);
	// Dodge i-frames and return-to-idle are driven by the dodge montage's notifies.
}

float UHCCombatComponent::ReceiveAttack(float IncomingDamage, float IncomingPoiseDamage, AActor* Attacker)
{
	// Parry: a hit within the parry window at the start of a block.
	if (AttackState == EHCAttackState::Blocking && GetWorld())
	{
		const float BlockElapsed = GetWorld()->GetTimeSeconds() - BlockStartTime;
		if (BlockElapsed <= ParryWindow)
		{
			SetAttackState(EHCAttackState::Parrying);
			OnParrySuccess.Broadcast(Attacker);
			UE_LOG(LogHollowCrown, Verbose, TEXT("%s parried %s"), *GetNameSafe(GetOwner()), *GetNameSafe(Attacker));
			return 0.f; // Parried attacks deal no damage and open the attacker to a riposte.
		}

		// Outside the window: a normal block. Reduce damage, no poise damage taken.
		return IncomingDamage * (1.f - BlockDamageReduction);
	}

	// Unblocked: full damage and poise damage.
	if (Attributes)
	{
		Attributes->ApplyPoiseDamage(IncomingPoiseDamage);
	}
	return IncomingDamage;
}

void UHCCombatComponent::OnAttackWindowOpen()
{
	if (AttackState != EHCAttackState::Windup && AttackState != EHCAttackState::Active)
	{
		return;
	}
	bAttackWindowOpen = true;
	SetAttackState(EHCAttackState::Active);
	PerformWeaponTrace();
}

void UHCCombatComponent::OnAttackWindowClose()
{
	bAttackWindowOpen = false;
	if (AttackState == EHCAttackState::Active)
	{
		SetAttackState(EHCAttackState::Recovery);
		// A subsequent montage-end notify (or input) returns the state to Idle.
	}
}

void UHCCombatComponent::PerformWeaponTrace()
{
	const AActor* Owner = GetOwner();
	if (!Owner || !EquippedWeapon || !GetWorld())
	{
		return;
	}

	const FVector Start = Owner->GetActorLocation();
	const FVector End = Start + Owner->GetActorForwardVector() * EquippedWeapon->Reach;

	TArray<FHitResult> Hits;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);

	// Sphere sweep approximates a weapon arc; production uses per-bone sockets on the weapon.
	const bool bHit = GetWorld()->SweepMultiByChannel(
		Hits, Start, End, FQuat::Identity, ECC_Pawn,
		FCollisionShape::MakeSphere(60.f), Params);

	if (!bHit)
	{
		return;
	}

	const float Damage = GetDamageForType(PendingAttackType);
	const float PoiseDmg = (PendingAttackType == EHCAttackType::Light) ? 0.f : EquippedWeapon->PoiseDamage;

	for (const FHitResult& Hit : Hits)
	{
		AActor* Target = Hit.GetActor();
		if (!Target || HitActorsThisSwing.Contains(Target))
		{
			continue;
		}
		HitActorsThisSwing.Add(Target);

		float AppliedDamage = Damage;
		// Let the target's combat component apply block/parry before health.
		if (UHCCombatComponent* TargetCombat = Target->FindComponentByClass<UHCCombatComponent>())
		{
			AppliedDamage = TargetCombat->ReceiveAttack(Damage, PoiseDmg, GetOwner());
		}
		else if (UHCAttributeComponent* TargetAttr = Target->FindComponentByClass<UHCAttributeComponent>())
		{
			TargetAttr->ApplyPoiseDamage(PoiseDmg);
		}

		if (AppliedDamage > 0.f)
		{
			if (UHCAttributeComponent* TargetAttr = Target->FindComponentByClass<UHCAttributeComponent>())
			{
				TargetAttr->ApplyHealthChange(-AppliedDamage, GetOwner());
			}
			OnHitLanded.Broadcast(Target, AppliedDamage);
		}
	}
}

void UHCCombatComponent::HandlePoiseBroken()
{
	OnOwnerPoiseBroken();
}

void UHCCombatComponent::OnOwnerPoiseBroken()
{
	EnterStagger();
}

void UHCCombatComponent::EnterStagger()
{
	SetAttackState(EHCAttackState::Staggered);
	OnStaggered.Broadcast();

	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(
			StaggerTimerHandle, this, &UHCCombatComponent::ExitStagger, StaggerDuration, false);
	}
}

void UHCCombatComponent::ExitStagger()
{
	if (AttackState == EHCAttackState::Staggered)
	{
		SetAttackState(EHCAttackState::Idle);
	}
}

void UHCCombatComponent::SetAttackState(EHCAttackState NewState)
{
	if (AttackState == NewState)
	{
		return;
	}
	AttackState = NewState;
	OnAttackStateChanged.Broadcast(NewState);
}

float UHCCombatComponent::GetDamageForType(EHCAttackType Type) const
{
	if (!EquippedWeapon)
	{
		return 0.f;
	}
	switch (Type)
	{
	case EHCAttackType::Light:   return EquippedWeapon->LightDamage;
	case EHCAttackType::Heavy:   return EquippedWeapon->HeavyDamage;
	case EHCAttackType::Charged: return EquippedWeapon->ChargedDamage;
	default:                     return EquippedWeapon->LightDamage;
	}
}

float UHCCombatComponent::GetStaminaCostForType(EHCAttackType Type) const
{
	if (!EquippedWeapon)
	{
		return 0.f;
	}
	switch (Type)
	{
	case EHCAttackType::Light:   return EquippedWeapon->LightStaminaCost;
	case EHCAttackType::Heavy:   return EquippedWeapon->HeavyStaminaCost;
	case EHCAttackType::Charged: return EquippedWeapon->ChargedStaminaCost;
	default:                     return EquippedWeapon->LightStaminaCost;
	}
}

UAnimMontage* UHCCombatComponent::GetMontageForType(EHCAttackType Type) const
{
	if (!EquippedWeapon)
	{
		return nullptr;
	}
	switch (Type)
	{
	case EHCAttackType::Light:
		return EquippedWeapon->LightComboMontages.Num() > 0 ? EquippedWeapon->LightComboMontages[0] : nullptr;
	case EHCAttackType::Heavy:
		return EquippedWeapon->HeavyMontage;
	case EHCAttackType::Charged:
		return EquippedWeapon->ChargedMontage;
	default:
		return nullptr;
	}
}
