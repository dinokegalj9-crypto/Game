// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HCAttributeComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FHCOnHealthChanged, UHCAttributeComponent*, Component, float, NewHealth, float, Delta, AActor*, Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnStaminaChanged, float, NewStamina);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnPoiseChanged, float, NewPoise);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHCOnPoiseBroken);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnDeath, AActor*, Killer);

/**
 * Shared vitals for any combatant (player, NPC, enemy, boss): health, stamina, and poise.
 * Composition-first: combat reads/writes stamina and poise here, survival applies
 * penalties here, and the world-state pipeline listens for OnDeath. See
 * Docs/Architecture.md and Docs/Systems/CombatSystem.md.
 */
UCLASS(ClassGroup = (HollowCrown), meta = (BlueprintSpawnableComponent))
class HOLLOWCROWN_API UHCAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHCAttributeComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Applies damage and broadcasts. Returns the actual amount applied. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Attributes")
	float ApplyHealthChange(float Delta, AActor* Instigator);

	/** Spends stamina if available; returns false (and spends nothing) if insufficient. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Attributes")
	bool TrySpendStamina(float Amount);

	/** Applies poise damage; if poise reaches zero, broadcasts OnPoiseBroken and staggers. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Attributes")
	void ApplyPoiseDamage(float Amount);

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Attributes")
	bool IsAlive() const { return Health > 0.f; }

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Attributes")
	float GetHealthPercent() const { return MaxHealth > 0.f ? Health / MaxHealth : 0.f; }

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Attributes")
	float GetStaminaPercent() const { return MaxStamina > 0.f ? Stamina / MaxStamina : 0.f; }

	/** Survival and corruption modifiers scale the effective max values. 1.0 = unmodified. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Attributes")
	void SetStaminaRegenMultiplier(float Multiplier) { StaminaRegenMultiplier = FMath::Max(0.f, Multiplier); }

	// --- Delegates ---
	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Attributes")
	FHCOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Attributes")
	FHCOnStaminaChanged OnStaminaChanged;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Attributes")
	FHCOnPoiseChanged OnPoiseChanged;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Attributes")
	FHCOnPoiseBroken OnPoiseBroken;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Attributes")
	FHCOnDeath OnDeath;

protected:
	// --- Health ---
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Health")
	float MaxHealth = 100.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Hollow Crown|Health")
	float Health = 100.f;

	// --- Stamina ---
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Stamina")
	float MaxStamina = 100.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Hollow Crown|Stamina")
	float Stamina = 100.f;

	/** Stamina regenerated per second once the regen delay has elapsed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Stamina")
	float StaminaRegenRate = 25.f;

	/** Seconds after spending stamina before regen resumes. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Stamina")
	float StaminaRegenDelay = 1.0f;

	// --- Poise ---
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Poise")
	float MaxPoise = 50.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Hollow Crown|Poise")
	float Poise = 50.f;

	/** Poise regenerated per second once the regen delay has elapsed. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Poise")
	float PoiseRegenRate = 15.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Poise")
	float PoiseRegenDelay = 2.0f;

private:
	float StaminaRegenMultiplier = 1.f;
	float TimeSinceStaminaUse = 0.f;
	float TimeSincePoiseDamage = 0.f;
	bool bDead = false;

	void RegenerateStamina(float DeltaTime);
	void RegeneratePoise(float DeltaTime);
	void HandleDeath(AActor* Killer);
};
