// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HCEnemyController.generated.h"

class UHCCombatComponent;

/**
 * Minimal "approach and strike" enemy brain for the combat gym: it faces the player, closes the
 * distance, and attacks on a cooldown when in range. Deliberately simple (direct movement input,
 * no NavMesh required) so a flat gym works with zero setup. Production enemies use a StateTree +
 * AI Perception + EQS on a NavMesh (see Docs/Systems/NPCSystem.md / TechnicalArchitecture.md).
 */
UCLASS()
class HOLLOWCROWN_API AHCEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	AHCEnemyController();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	/** Beyond this distance the enemy ignores the player. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|AI")
	float AcquireRadius = 1500.f;

	/** Within this distance the enemy stops closing and attacks. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|AI")
	float AttackRange = 180.f;

	/** Seconds between attack attempts. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|AI")
	float AttackInterval = 1.8f;

private:
	float AttackCooldown = 0.f;
	TWeakObjectPtr<UHCCombatComponent> Combat;
};
