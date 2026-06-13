// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Core/HCTypes.h"
#include "HCWeatherSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHCOnWeatherChanged, EHCWeatherType, OldWeather, EHCWeatherType, NewWeather);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHCOnBloodMoonStarted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHCOnBloodMoonEnded);

/**
 * Owns the active weather state and drives weighted, region-aware transitions over time.
 * Atmosphere first, mechanic second: combat, AI, survival, and audio subscribe to changes.
 * See Docs/Systems/WeatherSystem.md.
 */
UCLASS()
class HOLLOWCROWN_API UHCWeatherSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;

	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Weather")
	void SetWeather(EHCWeatherType NewWeather);

	/** Force a scripted weather state and pause automatic transitions for the given seconds. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Weather")
	void ForceWeather(EHCWeatherType NewWeather, float HoldSeconds);

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Weather")
	EHCWeatherType GetCurrentWeather() const { return CurrentWeather; }

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Weather")
	bool IsBloodMoon() const { return CurrentWeather == EHCWeatherType::BloodMoon; }

	/** Higher player corruption increases Blood Moon likelihood and severity. 0..1. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Weather")
	void SetCorruptionInfluence(float Alpha) { CorruptionInfluence = FMath::Clamp(Alpha, 0.f, 1.f); }

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Weather")
	FHCOnWeatherChanged OnWeatherChanged;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Weather")
	FHCOnBloodMoonStarted OnBloodMoonStarted;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Weather")
	FHCOnBloodMoonEnded OnBloodMoonEnded;

protected:
	/** Average seconds between natural weather changes. */
	UPROPERTY(EditDefaultsOnly, Category = "Hollow Crown|Weather")
	float AverageTransitionInterval = 180.f;

private:
	EHCWeatherType CurrentWeather = EHCWeatherType::Fog; // The Moors favor fog.
	float TimeUntilNextTransition = 0.f;
	float ForcedHoldRemaining = 0.f;
	float CorruptionInfluence = 0.f;

	EHCWeatherType PickNextWeather() const;
	void ScheduleNextTransition();
};
