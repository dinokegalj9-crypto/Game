// Copyright Hollow Crown Studio. All Rights Reserved.

#include "Survival/HCSurvivalComponent.h"
#include "Stats/HCAttributeComponent.h"
#include "GameFramework/Actor.h"

UHCSurvivalComponent::UHCSurvivalComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	// Survival changes slowly; ticking a few times per second is plenty.
	PrimaryComponentTick.TickInterval = 0.5f;
}

void UHCSurvivalComponent::BeginPlay()
{
	Super::BeginPlay();
	if (AActor* Owner = GetOwner())
	{
		Attributes = Owner->FindComponentByClass<UHCAttributeComponent>();
	}
}

void UHCSurvivalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateNeed(EHCSurvivalNeed::Food, Food, Food - FoodDrainPerSecond * DeltaTime);
	UpdateNeed(EHCSurvivalNeed::Rest, RestValue, RestValue - RestDrainPerSecond * DeltaTime);

	// Temperature comfort drifts toward how close ambient is to comfort.
	const float TempDelta = FMath::Abs(AmbientTemperature - ComfortTemperature);
	const float TargetComfort = FMath::Clamp(100.f - TempDelta * 4.f, 0.f, 100.f);
	UpdateNeed(EHCSurvivalNeed::Temperature, Temperature,
		FMath::FInterpTo(Temperature, TargetComfort, DeltaTime, 0.5f));

	// Disease worsens slowly until cured.
	if (DiseaseLevel > 0.f)
	{
		UpdateNeed(EHCSurvivalNeed::Disease, DiseaseLevel, FMath::Min(100.f, DiseaseLevel + 0.5f * DeltaTime));
	}

	ApplyPenalties();
}

void UHCSurvivalComponent::Eat(float Nourishment)
{
	UpdateNeed(EHCSurvivalNeed::Food, Food, Food + Nourishment);
}

void UHCSurvivalComponent::Rest(float Amount)
{
	UpdateNeed(EHCSurvivalNeed::Rest, RestValue, RestValue + Amount);
}

void UHCSurvivalComponent::ContractDisease(float Severity)
{
	UpdateNeed(EHCSurvivalNeed::Disease, DiseaseLevel, DiseaseLevel + Severity);
}

void UHCSurvivalComponent::Cure(float Amount)
{
	UpdateNeed(EHCSurvivalNeed::Disease, DiseaseLevel, DiseaseLevel - Amount);
	UpdateNeed(EHCSurvivalNeed::Injury, InjuryLevel, InjuryLevel - Amount);
}

float UHCSurvivalComponent::GetNeed(EHCSurvivalNeed Need) const
{
	switch (Need)
	{
	case EHCSurvivalNeed::Food:        return Food;
	case EHCSurvivalNeed::Rest:        return RestValue;
	case EHCSurvivalNeed::Temperature: return Temperature;
	case EHCSurvivalNeed::Disease:     return DiseaseLevel;
	case EHCSurvivalNeed::Injury:      return InjuryLevel;
	default:                           return 0.f;
	}
}

void UHCSurvivalComponent::UpdateNeed(EHCSurvivalNeed Need, float& Value, float NewValue)
{
	const float Clamped = FMath::Clamp(NewValue, 0.f, 100.f);
	if (FMath::IsNearlyEqual(Value, Clamped))
	{
		return;
	}

	const bool bWasOk = Value > CriticalThreshold;
	Value = Clamped;
	OnNeedChanged.Broadcast(Need, Value);

	// Food/Rest/Temperature are bad when low; Disease/Injury are bad when high.
	const bool bDepletionNeed = (Need == EHCSurvivalNeed::Food || Need == EHCSurvivalNeed::Rest || Need == EHCSurvivalNeed::Temperature);
	const bool bNowCritical = bDepletionNeed ? (Value <= CriticalThreshold) : (Value >= (100.f - CriticalThreshold));
	if (bNowCritical && (bDepletionNeed ? bWasOk : true))
	{
		OnNeedCritical.Broadcast(Need);
	}
}

void UHCSurvivalComponent::ApplyPenalties()
{
	if (!Attributes)
	{
		return;
	}

	// Low food/rest/temperature reduce stamina regen; this is the main "light" pressure.
	float Multiplier = 1.f;
	if (Food <= CriticalThreshold)        { Multiplier -= 0.3f; }
	if (RestValue <= CriticalThreshold)   { Multiplier -= 0.3f; }
	if (Temperature <= CriticalThreshold) { Multiplier -= 0.2f; }
	Attributes->SetStaminaRegenMultiplier(FMath::Max(0.1f, Multiplier));
}
