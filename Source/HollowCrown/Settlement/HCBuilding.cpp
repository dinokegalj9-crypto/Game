// Copyright Hollow Crown Studio. All Rights Reserved.

#include "Settlement/HCBuilding.h"
#include "Settlement/HCSettlementSubsystem.h"
#include "Engine/World.h"

AHCBuilding::AHCBuilding()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHCBuilding::BeginPlay()
{
	Super::BeginPlay();

	if (UWorld* World = GetWorld())
	{
		if (UHCSettlementSubsystem* Settlement = World->GetSubsystem<UHCSettlementSubsystem>())
		{
			Settlement->RegisterBuilding(this);
		}
	}
}

void AHCBuilding::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UWorld* World = GetWorld())
	{
		if (UHCSettlementSubsystem* Settlement = World->GetSubsystem<UHCSettlementSubsystem>())
		{
			Settlement->UnregisterBuilding(this);
		}
	}

	Super::EndPlay(EndPlayReason);
}
