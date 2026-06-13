// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/HCTypes.h"
#include "HCScheduleComponent.generated.h"

/** One time-blocked task in an NPC's day, anchored to a named world location. */
USTRUCT(BlueprintType)
struct FHCScheduleEntry
{
	GENERATED_BODY()

	/** Hour of day [0,24) at which this task begins. The latest entry <= now is active. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schedule")
	float StartHour = 0.f;

	/** Task name the Behavior Tree executes, e.g. "Sleep", "Work", "Eat", "Travel". */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schedule")
	FName Task = NAME_None;

	/** Named anchor location (home, workplace, market, church) the task uses. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Schedule")
	FName LocationTag = NAME_None;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnTaskChanged, FName, NewTask);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnFearStateChanged, EHCFearState, NewState);

/**
 * High-level "director" for a living NPC: picks the current scheduled task from the clock
 * and computes a fear state from nearby danger and the player's corruption stage. The
 * Behavior Tree executes whatever task this component reports. See Docs/Systems/NPCSystem.md.
 */
UCLASS(ClassGroup = (HollowCrown), meta = (BlueprintSpawnableComponent))
class HOLLOWCROWN_API UHCScheduleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHCScheduleComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Sets the current in-game hour [0,24); normally fed by the game's time-of-day clock. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|NPC")
	void UpdateTimeOfDay(float Hour);

	/** Reacts to the player's corruption stage (the NPC system's fear driver). */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|NPC")
	void ReactToCorruptionStage(EHCCorruptionStage PlayerStage);

	/** Reacts to immediate danger (perceived enemy / threat). Overrides corruption fear upward. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|NPC")
	void ReactToDanger(bool bDangerNearby);

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|NPC")
	FName GetCurrentTask() const { return CurrentTask; }

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|NPC")
	EHCFearState GetFearState() const { return FearState; }

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|NPC")
	FHCOnTaskChanged OnTaskChanged;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|NPC")
	FHCOnFearStateChanged OnFearStateChanged;

protected:
	/** The NPC's daily routine, authored per-NPC or via a UHCNPCProfile template. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hollow Crown|NPC")
	TArray<FHCScheduleEntry> ScheduleEntries;

private:
	FName CurrentTask = NAME_None;
	EHCFearState FearState = EHCFearState::Calm;
	bool bDanger = false;

	void SetTask(FName NewTask);
	void SetFearState(EHCFearState NewState);
	EHCFearState FearFromCorruptionStage(EHCCorruptionStage Stage) const;
};
