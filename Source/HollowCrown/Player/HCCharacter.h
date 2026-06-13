// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Core/HCTypes.h"
#include "HCCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHCAttributeComponent;
class UHCCombatComponent;
class UHCCorruptionComponent;
class UHCSurvivalComponent;
class UHCInventoryComponent;

/**
 * The Crownless — the player character. A thin assembly of gameplay components per the
 * composition-first architecture (Docs/Architecture.md §3). Input is wired via Enhanced
 * Input in the player controller, which forwards intent to the combat component.
 */
UCLASS()
class HOLLOWCROWN_API AHCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AHCCharacter();

	// --- Movement intent (called by the controller) ---
	void MoveInput(const FVector2D& Axis);
	void LookInput(const FVector2D& Axis);
	void SetSprinting(bool bSprint);

	// --- Combat intent (forwarded to the combat component) ---
	void DoLightAttack();
	void DoHeavyAttack();
	void DoChargedAttack();
	void StartBlocking();
	void StopBlocking();
	void DoDodge();
	void DoInteract();

	UFUNCTION(BlueprintPure, Category = "Hollow Crown")
	UHCCombatComponent* GetCombat() const { return Combat; }

	UFUNCTION(BlueprintPure, Category = "Hollow Crown")
	UHCCorruptionComponent* GetCorruption() const { return Corruption; }

	UFUNCTION(BlueprintPure, Category = "Hollow Crown")
	UHCInventoryComponent* GetInventory() const { return Inventory; }

protected:
	virtual void BeginPlay() override;

	// --- Camera ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hollow Crown|Camera")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hollow Crown|Camera")
	TObjectPtr<UCameraComponent> Camera;

	// --- Gameplay components ---
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hollow Crown|Components")
	TObjectPtr<UHCAttributeComponent> Attributes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hollow Crown|Components")
	TObjectPtr<UHCCombatComponent> Combat;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hollow Crown|Components")
	TObjectPtr<UHCCorruptionComponent> Corruption;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hollow Crown|Components")
	TObjectPtr<UHCSurvivalComponent> Survival;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hollow Crown|Components")
	TObjectPtr<UHCInventoryComponent> Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Movement")
	float WalkSpeed = 400.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Movement")
	float SprintSpeed = 650.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Movement")
	float SprintStaminaDrainPerSecond = 12.f;

	/**
	 * Reacts to crossing a corruption stage: drives the player's visual progression
	 * (mesh/material) and is the hook the rest of the world listens through. Marked
	 * BlueprintImplementableEvent so the visual swap is authored by artists.
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Hollow Crown|Corruption")
	void OnCorruptionStageChangedVisual(EHCCorruptionStage OldStage, EHCCorruptionStage NewStage);

private:
	bool bSprinting = false;

	UFUNCTION()
	void HandleCorruptionStageChanged(EHCCorruptionStage OldStage, EHCCorruptionStage NewStage);
};
