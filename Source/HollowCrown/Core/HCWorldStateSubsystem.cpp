// Copyright Hollow Crown Studio. All Rights Reserved.

#include "Core/HCWorldStateSubsystem.h"
#include "HollowCrown.h"

void UHCWorldStateSubsystem::ReportBossDefeated(FHCBossId BossId, const TArray<FName>& RegionsToUnlock)
{
	if (!BossId.IsValid() || DefeatedBosses.Contains(BossId))
	{
		return;
	}

	DefeatedBosses.Add(BossId);
	UE_LOG(LogHollowCrown, Log, TEXT("Boss defeated: %s (total %d)"), *BossId.Id.ToString(), DefeatedBosses.Num());

	OnBossDefeated.Broadcast(BossId);

	for (const FName& Region : RegionsToUnlock)
	{
		UnlockRegion(Region);
	}

	OnWorldStateChanged.Broadcast();
}

void UHCWorldStateSubsystem::UnlockRegion(FName RegionId)
{
	if (RegionId.IsNone() || UnlockedRegions.Contains(RegionId))
	{
		return;
	}

	UnlockedRegions.Add(RegionId);
	UE_LOG(LogHollowCrown, Log, TEXT("Region unlocked: %s"), *RegionId.ToString());
	OnRegionUnlocked.Broadcast(RegionId);
}

void UHCWorldStateSubsystem::SetFlag(FName Flag, bool bValue)
{
	if (Flag.IsNone())
	{
		return;
	}

	bool& Stored = ChoiceFlags.FindOrAdd(Flag);
	if (Stored != bValue)
	{
		Stored = bValue;
		OnWorldStateChanged.Broadcast();
	}
}

void UHCWorldStateSubsystem::CaptureState(TArray<FHCBossId>& OutBosses, TArray<FName>& OutRegions, TMap<FName, bool>& OutFlags) const
{
	OutBosses = DefeatedBosses.Array();
	OutRegions = UnlockedRegions.Array();
	OutFlags = ChoiceFlags;
}

void UHCWorldStateSubsystem::RestoreState(const TArray<FHCBossId>& InBosses, const TArray<FName>& InRegions, const TMap<FName, bool>& InFlags)
{
	DefeatedBosses.Reset();
	DefeatedBosses.Append(InBosses);

	UnlockedRegions.Reset();
	UnlockedRegions.Append(InRegions);

	ChoiceFlags = InFlags;

	OnWorldStateChanged.Broadcast();
}
