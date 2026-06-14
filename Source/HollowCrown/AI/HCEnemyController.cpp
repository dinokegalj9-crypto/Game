// Copyright Hollow Crown Studio. All Rights Reserved.

#include "AI/HCEnemyController.h"
#include "Combat/HCCombatComponent.h"
#include "Core/HCTypes.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

AHCEnemyController::AHCEnemyController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AHCEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	Combat = InPawn ? InPawn->FindComponentByClass<UHCCombatComponent>() : nullptr;
}

void AHCEnemyController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	APawn* Self = GetPawn();
	APawn* Target = UGameplayStatics::GetPlayerPawn(this, 0);
	if (!Self || !Target)
	{
		return;
	}

	if (AttackCooldown > 0.f)
	{
		AttackCooldown -= DeltaSeconds;
	}

	const FVector ToTarget = Target->GetActorLocation() - Self->GetActorLocation();
	const float Dist = ToTarget.Size2D();
	if (Dist > AcquireRadius)
	{
		return; // player out of range; idle
	}

	const FVector Dir = ToTarget.GetSafeNormal2D();
	if (!Dir.IsNearlyZero())
	{
		// Face the player (yaw only) — robust without orient-to-movement setup.
		FRotator Facing = Dir.Rotation();
		Facing.Pitch = 0.f;
		Facing.Roll = 0.f;
		Self->SetActorRotation(Facing);
	}

	if (Dist > AttackRange)
	{
		Self->AddMovementInput(Dir, 1.f);
	}
	else if (AttackCooldown <= 0.f && Combat.IsValid())
	{
		Combat->RequestAttack(EHCAttackType::Light);
		AttackCooldown = AttackInterval;
	}
}
