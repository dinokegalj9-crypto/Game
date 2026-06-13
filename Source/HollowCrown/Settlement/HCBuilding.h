// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataAsset.h"
#include "HCBuilding.generated.h"

/** Data-driven description of a placeable settlement structure. See SettlementSystem.md. */
UCLASS(BlueprintType)
class HOLLOWCROWN_API UHCBuildingDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	FName BuildingId = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	FText DisplayName;

	/** Prosperity contribution while standing and maintained. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	int32 ProsperityValue = 1;

	/** Population capacity this building adds (homes/barracks). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	int32 PopulationCapacity = 0;

	/** Crafting station tag this building provides (e.g. "Campfire", "Blacksmith"). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	FName StationTag = NAME_None;

	/** Other building ids that must exist before this can be built. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	TArray<FName> Prerequisites;
};

/** A placed building instance in the world. */
UCLASS()
class HOLLOWCROWN_API AHCBuilding : public AActor
{
	GENERATED_BODY()

public:
	AHCBuilding();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building")
	TObjectPtr<UHCBuildingDefinition> Definition = nullptr;

	UFUNCTION(BlueprintPure, Category = "Building")
	FName GetBuildingId() const { return Definition ? Definition->BuildingId : NAME_None; }

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
