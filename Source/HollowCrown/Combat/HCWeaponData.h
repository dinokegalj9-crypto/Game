// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Core/HCTypes.h"
#include "HCWeaponData.generated.h"

class UAnimMontage;

/**
 * Data-driven definition of a weapon and its moveset. Swapping the active UHCWeaponData on
 * the combat component swaps behavior and animations without code changes. See
 * Docs/Systems/CombatSystem.md.
 */
UCLASS(BlueprintType)
class HOLLOWCROWN_API UHCWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	FName WeaponId = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	EHCWeaponClass WeaponClass = EHCWeaponClass::Sword;

	// --- Damage & costs ---
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Damage")
	float LightDamage = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Damage")
	float HeavyDamage = 30.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Damage")
	float ChargedDamage = 50.f;

	/** Poise damage dealt by heavy/charged attacks; drives the stagger loop. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Damage")
	float PoiseDamage = 20.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Stamina")
	float LightStaminaCost = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Stamina")
	float HeavyStaminaCost = 22.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Stamina")
	float ChargedStaminaCost = 30.f;

	/** Trace length for melee hit detection, in cm. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float Reach = 180.f;

	// --- Moveset montages (assigned in the editor) ---
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Montages")
	TArray<TObjectPtr<UAnimMontage>> LightComboMontages;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Montages")
	TObjectPtr<UAnimMontage> HeavyMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Montages")
	TObjectPtr<UAnimMontage> ChargedMontage = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Montages")
	TObjectPtr<UAnimMontage> ExecutionMontage = nullptr;
};
