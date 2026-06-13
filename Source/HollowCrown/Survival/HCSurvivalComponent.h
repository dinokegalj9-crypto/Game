// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/HCTypes.h"
#include "HCSurvivalComponent.generated.h"

class UHCAttributeComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHCOnNeedChanged, EHCSurvivalNeed, Need, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnNeedCritical, EHCSurvivalNeed, Need);

/**
 * Light survival: food, rest, temperature, disease, injury. Decay is slow and
 * consequences are gradual (penalties to stamina/health via UHCAttributeComponent), never
 * sudden death from a neglected meter. See Docs/Systems/SurvivalSystem.md.
 */
UCLASS(ClassGroup = (HollowCrown), meta = (BlueprintSpawnableComponent))
class HOLLOWCROWN_API UHCSurvivalComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHCSurvivalComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Survival")
	void Eat(float Nourishment);

	/** Advances rest recovery; called when sleeping at a tent/home/safe campfire. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Survival")
	void Rest(float Amount);

	/** External temperature influence, e.g. from weather or a nearby campfire. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Survival")
	void SetAmbientTemperature(float Celsius) { AmbientTemperature = Celsius; }

	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Survival")
	void ContractDisease(float Severity);

	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Survival")
	void Cure(float Amount);

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Survival")
	float GetNeed(EHCSurvivalNeed Need) const;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Survival")
	FHCOnNeedChanged OnNeedChanged;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Survival")
	FHCOnNeedCritical OnNeedCritical;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Survival")
	float FoodDrainPerSecond = 0.05f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Survival")
	float RestDrainPerSecond = 0.04f;

	/** Value at or below which a need is "critical" and applies penalties. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Survival")
	float CriticalThreshold = 20.f;

	/** Comfortable ambient temperature in Celsius; deviation drives the temperature need. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Survival")
	float ComfortTemperature = 18.f;

private:
	float Food = 100.f;
	float RestValue = 100.f;
	float Temperature = 100.f; // comfort score 0..100, not degrees
	float DiseaseLevel = 0.f;
	float InjuryLevel = 0.f;
	float AmbientTemperature = 12.f;

	UPROPERTY()
	TObjectPtr<UHCAttributeComponent> Attributes = nullptr;

	void UpdateNeed(EHCSurvivalNeed Need, float& Value, float NewValue);
	void ApplyPenalties();
};
