// Copyright Hollow Crown Studio. All Rights Reserved.

#include "AI/HCNPCBase.h"
#include "Stats/HCAttributeComponent.h"
#include "AI/HCScheduleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HollowCrown.h"

AHCNPCBase::AHCNPCBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Attributes = CreateDefaultSubobject<UHCAttributeComponent>(TEXT("Attributes"));
	Schedule = CreateDefaultSubobject<UHCScheduleComponent>(TEXT("Schedule"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AHCNPCBase::BeginPlay()
{
	Super::BeginPlay();

	if (Attributes)
	{
		Attributes->OnDeath.AddDynamic(this, &AHCNPCBase::HandleDeath);
	}
}

void AHCNPCBase::HandleDeath(AActor* Killer)
{
	UE_LOG(LogHollowCrown, Verbose, TEXT("NPC %s died."), *NPCName.ToString());
	// Ragdoll / disable input / loot drop are handled in the Blueprint subclass or here
	// in a fuller implementation; kept minimal at the scaffolding stage.
	if (UCharacterMovementComponent* Move = GetCharacterMovement())
	{
		Move->DisableMovement();
	}
}
