// Copyright Hollow Crown Studio. All Rights Reserved.

#include "Corruption/HCCorruptionComponent.h"
#include "HollowCrown.h"

UHCCorruptionComponent::UHCCorruptionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHCCorruptionComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentStage = EvaluateStage(Corruption);
}

void UHCCorruptionComponent::AddCorruption(float Amount)
{
	if (Amount <= 0.f)
	{
		return;
	}
	SetCorruption(Corruption + Amount);
}

void UHCCorruptionComponent::RemoveCorruption(float Amount)
{
	if (Amount <= 0.f)
	{
		return;
	}
	SetCorruption(Corruption - Amount);
}

void UHCCorruptionComponent::RestoreState(float SavedCorruption)
{
	SetCorruption(SavedCorruption);
}

void UHCCorruptionComponent::SetCorruption(float NewValue)
{
	const float OldValue = Corruption;
	Corruption = FMath::Clamp(NewValue, 0.f, MaxCorruption);

	if (FMath::IsNearlyEqual(OldValue, Corruption))
	{
		return;
	}

	OnCorruptionChanged.Broadcast(OldValue, Corruption);

	const EHCCorruptionStage NewStage = EvaluateStage(Corruption);
	if (NewStage != CurrentStage)
	{
		const EHCCorruptionStage OldStage = CurrentStage;
		CurrentStage = NewStage;
		UE_LOG(LogHollowCrown, Log, TEXT("Corruption stage changed: %d -> %d (value %.1f)"),
			static_cast<int32>(OldStage), static_cast<int32>(NewStage), Corruption);
		OnCorruptionStageChanged.Broadcast(OldStage, NewStage);
	}
}

EHCCorruptionStage UHCCorruptionComponent::EvaluateStage(float Value) const
{
	// Walk thresholds high-to-low; the first one we meet or exceed is our stage.
	const int32 LastIndex = StageThresholds.Num() - 1;
	for (int32 i = LastIndex; i >= 0; --i)
	{
		if (Value >= StageThresholds[i])
		{
			return static_cast<EHCCorruptionStage>(i);
		}
	}
	return EHCCorruptionStage::Stage1_Human;
}
