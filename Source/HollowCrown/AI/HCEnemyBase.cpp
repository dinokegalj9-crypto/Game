// Copyright Hollow Crown Studio. All Rights Reserved.

#include "AI/HCEnemyBase.h"
#include "AI/HCEnemyController.h"
#include "Combat/HCCombatComponent.h"

AHCEnemyBase::AHCEnemyBase()
{
	Combat = CreateDefaultSubobject<UHCCombatComponent>(TEXT("Combat"));

	// Possessed by the gym brain by default; swap for a StateTree controller in production.
	AIControllerClass = AHCEnemyController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AHCEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	if (Combat && DefaultWeapon)
	{
		Combat->EquipWeapon(DefaultWeapon);
	}
}
