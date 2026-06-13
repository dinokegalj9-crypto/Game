// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/HCTypes.h"
#include "HCCorruptionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHCOnCorruptionChanged, float, OldValue, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHCOnCorruptionStageChanged, EHCCorruptionStage, OldStage, EHCCorruptionStage, NewStage);

/**
 * The signature mechanic. Tracks a 0..100 corruption value and maps it onto five stages.
 * Gaining corruption grants power; crossing a stage threshold makes the player less human,
 * which NPC fear, player visuals, and ending logic all react to. See
 * Docs/Systems/CorruptionSystem.md.
 */
UCLASS(ClassGroup = (HollowCrown), meta = (BlueprintSpawnableComponent))
class HOLLOWCROWN_API UHCCorruptionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHCCorruptionComponent();

	/** Adds corruption (typically a Crown fragment from a defeated boss) and re-evaluates stage. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Corruption")
	void AddCorruption(float Amount);

	/**
	 * Reduces corruption. Intended to be rare and story-significant, not a routine sink;
	 * see the design note in CorruptionSystem.md.
	 */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Corruption")
	void RemoveCorruption(float Amount);

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Corruption")
	float GetCorruption() const { return Corruption; }

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Corruption")
	EHCCorruptionStage GetStage() const { return CurrentStage; }

	/** Convenience for systems that scale linearly with corruption (e.g. monster attraction). */
	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Corruption")
	float GetCorruptionAlpha() const { return MaxCorruption > 0.f ? Corruption / MaxCorruption : 0.f; }

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Corruption")
	FHCOnCorruptionChanged OnCorruptionChanged;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Corruption")
	FHCOnCorruptionStageChanged OnCorruptionStageChanged;

	// --- Save support (see Docs/Systems/SaveSystem.md) ---
	float CaptureState() const { return Corruption; }
	void RestoreState(float SavedCorruption);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Corruption")
	float MaxCorruption = 100.f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Hollow Crown|Corruption")
	float Corruption = 0.f;

	/**
	 * Lower-bound value at which each stage begins. Index 0 is implicitly 0 (Stage 1).
	 * Tunable per the design table; kept data-driven rather than hardcoded in logic.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Corruption")
	TArray<float> StageThresholds = { 0.f, 20.f, 45.f, 70.f, 90.f };

private:
	EHCCorruptionStage CurrentStage = EHCCorruptionStage::Stage1_Human;

	/** Maps a corruption value to its stage using StageThresholds. */
	EHCCorruptionStage EvaluateStage(float Value) const;

	/** Applies a clamped corruption value and broadcasts change + stage-change as needed. */
	void SetCorruption(float NewValue);
};
