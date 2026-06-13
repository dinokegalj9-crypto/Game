// Copyright Hollow Crown Studio. All Rights Reserved.

#include "Stats/HCAttributeComponent.h"
#include "HollowCrown.h"

UHCAttributeComponent::UHCAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UHCAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	Stamina = MaxStamina;
	Poise = MaxPoise;
}

void UHCAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bDead)
	{
		return;
	}

	TimeSinceStaminaUse += DeltaTime;
	TimeSincePoiseDamage += DeltaTime;

	RegenerateStamina(DeltaTime);
	RegeneratePoise(DeltaTime);
}

float UHCAttributeComponent::ApplyHealthChange(float Delta, AActor* Instigator)
{
	if (bDead || FMath::IsNearlyZero(Delta))
	{
		return 0.f;
	}

	const float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.f, MaxHealth);
	const float ActualDelta = Health - OldHealth;

	if (!FMath::IsNearlyZero(ActualDelta))
	{
		OnHealthChanged.Broadcast(this, Health, ActualDelta, Instigator);
	}

	if (Health <= 0.f)
	{
		HandleDeath(Instigator);
	}

	return ActualDelta;
}

bool UHCAttributeComponent::TrySpendStamina(float Amount)
{
	if (Amount <= 0.f)
	{
		return true;
	}

	if (Stamina < Amount)
	{
		return false;
	}

	Stamina -= Amount;
	TimeSinceStaminaUse = 0.f;
	OnStaminaChanged.Broadcast(Stamina);
	return true;
}

void UHCAttributeComponent::ApplyPoiseDamage(float Amount)
{
	if (bDead || Amount <= 0.f)
	{
		return;
	}

	Poise = FMath::Max(0.f, Poise - Amount);
	TimeSincePoiseDamage = 0.f;
	OnPoiseChanged.Broadcast(Poise);

	if (FMath::IsNearlyZero(Poise))
	{
		OnPoiseBroken.Broadcast();
		// Poise refills after a break so the actor isn't perma-stunned; the combat
		// component owns the stagger duration and execution window.
		Poise = MaxPoise;
	}
}

void UHCAttributeComponent::RegenerateStamina(float DeltaTime)
{
	if (Stamina >= MaxStamina || TimeSinceStaminaUse < StaminaRegenDelay)
	{
		return;
	}

	Stamina = FMath::Min(MaxStamina, Stamina + StaminaRegenRate * StaminaRegenMultiplier * DeltaTime);
	OnStaminaChanged.Broadcast(Stamina);
}

void UHCAttributeComponent::RegeneratePoise(float DeltaTime)
{
	if (Poise >= MaxPoise || TimeSincePoiseDamage < PoiseRegenDelay)
	{
		return;
	}

	Poise = FMath::Min(MaxPoise, Poise + PoiseRegenRate * DeltaTime);
	OnPoiseChanged.Broadcast(Poise);
}

void UHCAttributeComponent::HandleDeath(AActor* Killer)
{
	if (bDead)
	{
		return;
	}

	bDead = true;
	UE_LOG(LogHollowCrown, Verbose, TEXT("%s died."), *GetNameSafe(GetOwner()));
	OnDeath.Broadcast(Killer);
}
