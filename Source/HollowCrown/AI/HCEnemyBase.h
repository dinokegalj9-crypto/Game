// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AI/HCNPCBase.h"
#include "HCEnemyBase.generated.h"

class UHCCombatComponent;
class UHCWeaponData;

/**
 * Base hostile NPC. Extends the living-NPC base with a combat component and is possessed by
 * AHCEnemyController. Assign a DefaultWeapon (a DA_WeaponData) so it can deal damage. This is the
 * gym's punching bag and the foundation enemy archetypes/minibosses build on (data-driven, per
 * Docs/Systems/NPCSystem.md). See Docs/GymSetup.md.
 */
UCLASS()
class HOLLOWCROWN_API AHCEnemyBase : public AHCNPCBase
{
	GENERATED_BODY()

public:
	AHCEnemyBase();

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Enemy")
	UHCCombatComponent* GetCombat() const { return Combat; }

protected:
	virtual void BeginPlay() override;

	/** Combatant behaviour (uses the same component as the player). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hollow Crown|Enemy")
	TObjectPtr<UHCCombatComponent> Combat;

	/** Weapon equipped on spawn so attacks deal damage. Assign a DA_WeaponData in the Blueprint. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hollow Crown|Enemy")
	TObjectPtr<UHCWeaponData> DefaultWeapon;
};
