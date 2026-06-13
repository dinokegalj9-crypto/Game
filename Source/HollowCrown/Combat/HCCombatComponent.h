// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/HCTypes.h"
#include "HCCombatComponent.generated.h"

class UHCAttributeComponent;
class UHCWeaponData;
class UAnimMontage;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnAttackStateChanged, EHCAttackState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHCOnHitLanded, AActor*, Target, float, Damage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnParrySuccess, AActor*, Attacker);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHCOnStaggered);

/**
 * Drives heavy, grounded melee combat: a small attack state machine, weapon-trace hit
 * detection, blocking/parry, dodge, and the stagger/execution loop. Reads stamina and
 * poise from the owner's UHCAttributeComponent. See Docs/Systems/CombatSystem.md.
 */
UCLASS(ClassGroup = (HollowCrown), meta = (BlueprintSpawnableComponent))
class HOLLOWCROWN_API UHCCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHCCombatComponent();

	// --- Inputs (called by the player controller or AI) ---
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Combat")
	void RequestAttack(EHCAttackType AttackType);

	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Combat")
	void StartBlock();

	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Combat")
	void StopBlock();

	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Combat")
	void RequestDodge();

	/** Equips a weapon's data/moveset. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Combat")
	void EquipWeapon(UHCWeaponData* Weapon);

	/**
	 * Routes incoming damage through block/parry logic before health. Returns the damage
	 * that should actually be applied to health (0 if fully parried/blocked away).
	 */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Combat")
	float ReceiveAttack(float IncomingDamage, float IncomingPoiseDamage, AActor* Attacker);

	// --- Animation-notify hooks: the montage drives the active hit window ---
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Combat")
	void OnAttackWindowOpen();

	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Combat")
	void OnAttackWindowClose();

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Combat")
	EHCAttackState GetAttackState() const { return AttackState; }

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Combat")
	bool IsStaggered() const { return AttackState == EHCAttackState::Staggered; }

	// --- Delegates ---
	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Combat")
	FHCOnAttackStateChanged OnAttackStateChanged;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Combat")
	FHCOnHitLanded OnHitLanded;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Combat")
	FHCOnParrySuccess OnParrySuccess;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Combat")
	FHCOnStaggered OnStaggered;

protected:
	virtual void BeginPlay() override;

	/** Currently equipped weapon definition. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Combat")
	TObjectPtr<UHCWeaponData> EquippedWeapon = nullptr;

	/** Window (seconds) at the start of a block in which a hit counts as a parry. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Combat")
	float ParryWindow = 0.2f;

	/** Fraction of damage absorbed by a (non-parry) block. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Combat")
	float BlockDamageReduction = 0.7f;

	/** Duration of the stagger/execution window after poise breaks. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Combat")
	float StaggerDuration = 2.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Combat")
	float DodgeStaminaCost = 15.f;

private:
	EHCAttackState AttackState = EHCAttackState::Idle;
	EHCAttackType PendingAttackType = EHCAttackType::Light;
	bool bAttackWindowOpen = false;
	float BlockStartTime = 0.f;

	/** Actors already hit during the current active window (no double hits per swing). */
	UPROPERTY()
	TSet<TObjectPtr<AActor>> HitActorsThisSwing;

	FTimerHandle StaggerTimerHandle;

	/** Cached sibling attribute component on the owner. */
	UPROPERTY()
	TObjectPtr<UHCAttributeComponent> Attributes = nullptr;

	void SetAttackState(EHCAttackState NewState);
	bool CanStartNewAction() const;
	float GetDamageForType(EHCAttackType Type) const;
	float GetStaminaCostForType(EHCAttackType Type) const;
	UAnimMontage* GetMontageForType(EHCAttackType Type) const;
	void PerformWeaponTrace();
	void EnterStagger();
	void ExitStagger();
	void OnOwnerPoiseBroken();

	UFUNCTION()
	void HandlePoiseBroken();
};
