// Copyright Hollow Crown Studio. All Rights Reserved.

#include "AI/HCScheduleComponent.h"
#include "HollowCrown.h"

UHCScheduleComponent::UHCScheduleComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHCScheduleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHCScheduleComponent::UpdateTimeOfDay(float Hour)
{
	if (ScheduleEntries.Num() == 0)
	{
		return;
	}

	// The active task is the latest entry whose StartHour is <= the current hour,
	// wrapping to the last entry of the previous day if none qualify yet.
	const FHCScheduleEntry* Active = nullptr;
	for (const FHCScheduleEntry& Entry : ScheduleEntries)
	{
		if (Entry.StartHour <= Hour && (!Active || Entry.StartHour >= Active->StartHour))
		{
			Active = &Entry;
		}
	}
	if (!Active)
	{
		// Before the first entry of the day: carry over the last (late-night) task.
		Active = &ScheduleEntries.Last();
	}

	SetTask(Active->Task);
}

void UHCScheduleComponent::ReactToCorruptionStage(EHCCorruptionStage PlayerStage)
{
	if (bDanger)
	{
		return; // Immediate danger takes precedence over ambient corruption dread.
	}
	SetFearState(FearFromCorruptionStage(PlayerStage));
}

void UHCScheduleComponent::ReactToDanger(bool bDangerNearby)
{
	bDanger = bDangerNearby;
	if (bDanger)
	{
		SetFearState(EHCFearState::Fleeing);
	}
}

EHCFearState UHCScheduleComponent::FearFromCorruptionStage(EHCCorruptionStage Stage) const
{
	switch (Stage)
	{
	case EHCCorruptionStage::Stage1_Human:    return EHCFearState::Calm;
	case EHCCorruptionStage::Stage2_DarkEyes: return EHCFearState::Uneasy;
	case EHCCorruptionStage::Stage3_Veins:    return EHCFearState::Uneasy;
	case EHCCorruptionStage::Stage4_Monstrous:return EHCFearState::Fearful;
	case EHCCorruptionStage::Stage5_Inhuman:  return EHCFearState::Fleeing;
	default:                                  return EHCFearState::Calm;
	}
}

void UHCScheduleComponent::SetTask(FName NewTask)
{
	if (CurrentTask == NewTask)
	{
		return;
	}
	CurrentTask = NewTask;
	OnTaskChanged.Broadcast(NewTask);
}

void UHCScheduleComponent::SetFearState(EHCFearState NewState)
{
	if (FearState == NewState)
	{
		return;
	}
	FearState = NewState;
	OnFearStateChanged.Broadcast(NewState);
}
