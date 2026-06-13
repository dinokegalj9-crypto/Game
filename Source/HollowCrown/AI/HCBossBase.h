// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AI/HCNPCBase.h"
#include "HCBossBase.generated.h"

class UHCBossDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnBossDefeated_Actor, AHCBossBase*, Boss);

/**
 * Base class for major bosses. On death it executes the four guarantees from Design Bible
 * §7 through the world-state pipeline (Architecture §5): grants the player the boss's
 * Crown fragment (corruption) and ability, then reports the kill to the world-state
 * subsystem, which unlocks regions and broadcasts the world change.
 */
UCLASS()
class HOLLOWCROWN_API AHCBossBase : public AHCNPCBase
{
	GENERATED_BODY()

public:
	AHCBossBase();

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Boss")
	bool IsDefeated() const { return bDefeated; }

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Boss")
	FHCOnBossDefeated_Actor OnBossDefeatedActor;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hollow Crown|Boss")
	TObjectPtr<UHCBossDefinition> BossDefinition = nullptr;

	/** Authored cinematic / world dressing on defeat (art-side). */
	UFUNCTION(BlueprintImplementableEvent, Category = "Hollow Crown|Boss")
	void OnDefeatedPresentation();

private:
	bool bDefeated = false;

	UFUNCTION()
	void HandleBossDeath(AActor* Killer);

	/** Runs the four boss-death guarantees. */
	void ExecuteDeathConsequences(AActor* Killer);
};
