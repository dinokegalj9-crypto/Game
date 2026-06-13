// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "HCSettlementSubsystem.generated.h"

class AHCBuilding;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnBuildingPlaced, AHCBuilding*, Building);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnBuildingRemoved, AHCBuilding*, Building);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHCOnProsperityChanged, int32, OldValue, int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHCOnSettlementCollapsed);

/**
 * Tracks the player's settlement: placed buildings, aggregate prosperity, population
 * capacity, and available crafting stations. Buildings register themselves on spawn. The
 * settlement can prosper or collapse. See Docs/Systems/SettlementSystem.md.
 */
UCLASS()
class HOLLOWCROWN_API UHCSettlementSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Settlement")
	void RegisterBuilding(AHCBuilding* Building);

	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Settlement")
	void UnregisterBuilding(AHCBuilding* Building);

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Settlement")
	int32 GetProsperity() const { return Prosperity; }

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Settlement")
	int32 GetPopulationCapacity() const { return PopulationCapacity; }

	/** Whether a crafting station of the given tag is available in the settlement. */
	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Settlement")
	bool HasStation(FName StationTag) const;

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Settlement")
	bool HasBuilding(FName BuildingId) const;

	/** Reduces prosperity (raids, disease, neglect, high corruption); may trigger collapse. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Settlement")
	void ApplyProsperityPenalty(int32 Amount);

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Settlement")
	FHCOnBuildingPlaced OnBuildingPlaced;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Settlement")
	FHCOnBuildingRemoved OnBuildingRemoved;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Settlement")
	FHCOnProsperityChanged OnProsperityChanged;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Settlement")
	FHCOnSettlementCollapsed OnSettlementCollapsed;

protected:
	/** Prosperity at or below this is considered collapse. */
	UPROPERTY(EditDefaultsOnly, Category = "Hollow Crown|Settlement")
	int32 CollapseThreshold = 0;

private:
	UPROPERTY()
	TArray<TObjectPtr<AHCBuilding>> Buildings;

	int32 Prosperity = 0;
	int32 PopulationCapacity = 0;
	int32 ProsperityPenalty = 0;

	void Recalculate();
};
