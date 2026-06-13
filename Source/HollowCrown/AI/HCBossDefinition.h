// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Core/HCTypes.h"
#include "HCBossDefinition.generated.h"

/**
 * Data-driven description of a major boss and the four guarantees its death must satisfy
 * (Design Bible §7): change the world, grant an ability, advance corruption, unlock areas.
 */
UCLASS(BlueprintType)
class HOLLOWCROWN_API UHCBossDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boss")
	FHCBossId BossId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boss")
	FText DisplayName;

	/** Crown-fragment corruption granted to the player on death. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boss")
	float CorruptionReward = 25.f;

	/** Identifier of the ability unlocked by absorbing this fragment. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boss")
	FName GrantedAbilityId = NAME_None;

	/** Regions this boss's death opens. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Boss")
	TArray<FName> RegionsToUnlock;
};
