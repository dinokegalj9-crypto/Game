// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Core/HCTypes.h"
#include "HCWorldStateSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnBossDefeated, FHCBossId, BossId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnRegionUnlocked, FName, RegionId);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHCOnWorldStateChanged);

/**
 * Authoritative record of persistent world state: which bosses are dead, which regions
 * are unlocked, and named permanent-choice flags. This is the hub of the boss-death
 * pipeline described in Docs/Architecture.md §5 and the primary thing the save system
 * serializes. Systems broadcast/subscribe here rather than referencing each other.
 */
UCLASS()
class HOLLOWCROWN_API UHCWorldStateSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	/**
	 * Single entry point for "a boss died". Records the kill, unlocks the regions the boss
	 * gated, and broadcasts. The caller (the boss actor) is responsible for granting the
	 * boss's ability and corruption; this subsystem owns world consequences.
	 */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|World State")
	void ReportBossDefeated(FHCBossId BossId, const TArray<FName>& RegionsToUnlock);

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|World State")
	bool IsBossDefeated(FHCBossId BossId) const { return DefeatedBosses.Contains(BossId); }

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|World State")
	bool IsRegionUnlocked(FName RegionId) const { return UnlockedRegions.Contains(RegionId); }

	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|World State")
	void UnlockRegion(FName RegionId);

	/** Generic named flag for permanent story choices (e.g. "SparedSaintEleanor"). */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|World State")
	void SetFlag(FName Flag, bool bValue);

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|World State")
	bool GetFlag(FName Flag) const { return ChoiceFlags.Contains(Flag) && ChoiceFlags[Flag]; }

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|World State")
	int32 GetDefeatedBossCount() const { return DefeatedBosses.Num(); }

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|World State")
	FHCOnBossDefeated OnBossDefeated;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|World State")
	FHCOnRegionUnlocked OnRegionUnlocked;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|World State")
	FHCOnWorldStateChanged OnWorldStateChanged;

	// --- Save support (see Docs/Systems/SaveSystem.md) ---
	void CaptureState(TArray<FHCBossId>& OutBosses, TArray<FName>& OutRegions, TMap<FName, bool>& OutFlags) const;
	void RestoreState(const TArray<FHCBossId>& InBosses, const TArray<FName>& InRegions, const TMap<FName, bool>& InFlags);

private:
	UPROPERTY()
	TSet<FHCBossId> DefeatedBosses;

	UPROPERTY()
	TSet<FName> UnlockedRegions;

	UPROPERTY()
	TMap<FName, bool> ChoiceFlags;
};
