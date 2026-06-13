// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Core/HCTypes.h"
#include "Inventory/HCItemDefinition.h"
#include "HCSaveGame.generated.h"

/**
 * Serializable snapshot of everything that must persist (Docs/Systems/SaveSystem.md).
 * The save subsystem fills this from the world-state, player, inventory, and settlement,
 * and distributes it back on load. Carries a version for forward migration.
 */
UCLASS()
class HOLLOWCROWN_API UHCSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	/** Bump when the save shape changes; load-time migration keys off this. */
	UPROPERTY() int32 SaveVersion = 1;

	UPROPERTY() FString RegionId;
	UPROPERTY() FDateTime Timestamp;
	UPROPERTY() float PlaytimeSeconds = 0.f;

	// --- World state ---
	UPROPERTY() TArray<FHCBossId> DefeatedBosses;
	UPROPERTY() TArray<FName> UnlockedRegions;
	UPROPERTY() TMap<FName, bool> ChoiceFlags;

	// --- Player ---
	UPROPERTY() FTransform PlayerTransform;
	UPROPERTY() float Corruption = 0.f;
	UPROPERTY() TArray<FHCItemStack> Inventory;

	// --- Settlement ---
	UPROPERTY() int32 SettlementProsperity = 0;
	UPROPERTY() TArray<FName> PlacedBuildingIds;
};
