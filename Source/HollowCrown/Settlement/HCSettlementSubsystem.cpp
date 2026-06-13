// Copyright Hollow Crown Studio. All Rights Reserved.

#include "Settlement/HCSettlementSubsystem.h"
#include "Settlement/HCBuilding.h"
#include "HollowCrown.h"

void UHCSettlementSubsystem::RegisterBuilding(AHCBuilding* Building)
{
	if (!Building || Buildings.Contains(Building))
	{
		return;
	}
	Buildings.Add(Building);
	Recalculate();
	OnBuildingPlaced.Broadcast(Building);
}

void UHCSettlementSubsystem::UnregisterBuilding(AHCBuilding* Building)
{
	if (!Building || !Buildings.Contains(Building))
	{
		return;
	}
	Buildings.Remove(Building);
	Recalculate();
	OnBuildingRemoved.Broadcast(Building);
}

bool UHCSettlementSubsystem::HasStation(FName StationTag) const
{
	if (StationTag.IsNone())
	{
		return true;
	}
	for (const AHCBuilding* Building : Buildings)
	{
		if (Building && Building->Definition && Building->Definition->StationTag == StationTag)
		{
			return true;
		}
	}
	return false;
}

bool UHCSettlementSubsystem::HasBuilding(FName BuildingId) const
{
	for (const AHCBuilding* Building : Buildings)
	{
		if (Building && Building->GetBuildingId() == BuildingId)
		{
			return true;
		}
	}
	return false;
}

void UHCSettlementSubsystem::ApplyProsperityPenalty(int32 Amount)
{
	if (Amount <= 0)
	{
		return;
	}
	ProsperityPenalty += Amount;
	Recalculate();
}

void UHCSettlementSubsystem::Recalculate()
{
	const int32 OldProsperity = Prosperity;

	int32 RawProsperity = 0;
	PopulationCapacity = 0;
	for (const AHCBuilding* Building : Buildings)
	{
		if (Building && Building->Definition)
		{
			RawProsperity += Building->Definition->ProsperityValue;
			PopulationCapacity += Building->Definition->PopulationCapacity;
		}
	}

	Prosperity = RawProsperity - ProsperityPenalty;

	if (Prosperity != OldProsperity)
	{
		OnProsperityChanged.Broadcast(OldProsperity, Prosperity);
	}

	if (Prosperity <= CollapseThreshold && Buildings.Num() > 0)
	{
		UE_LOG(LogHollowCrown, Warning, TEXT("Settlement has collapsed (prosperity %d)."), Prosperity);
		OnSettlementCollapsed.Broadcast();
	}
}
