// Copyright Hollow Crown Studio. All Rights Reserved.

#include "World/HCWeatherSubsystem.h"
#include "HollowCrown.h"

void UHCWeatherSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	ScheduleNextTransition();
}

TStatId UHCWeatherSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UHCWeatherSubsystem, STATGROUP_Tickables);
}

void UHCWeatherSubsystem::Tick(float DeltaTime)
{
	if (ForcedHoldRemaining > 0.f)
	{
		ForcedHoldRemaining -= DeltaTime;
		return;
	}

	TimeUntilNextTransition -= DeltaTime;
	if (TimeUntilNextTransition <= 0.f)
	{
		SetWeather(PickNextWeather());
		ScheduleNextTransition();
	}
}

void UHCWeatherSubsystem::SetWeather(EHCWeatherType NewWeather)
{
	if (NewWeather == CurrentWeather)
	{
		return;
	}

	const EHCWeatherType OldWeather = CurrentWeather;
	const bool bWasBloodMoon = (OldWeather == EHCWeatherType::BloodMoon);
	const bool bIsBloodMoon = (NewWeather == EHCWeatherType::BloodMoon);

	CurrentWeather = NewWeather;
	UE_LOG(LogHollowCrown, Log, TEXT("Weather: %d -> %d"), static_cast<int32>(OldWeather), static_cast<int32>(NewWeather));
	OnWeatherChanged.Broadcast(OldWeather, NewWeather);

	if (bIsBloodMoon && !bWasBloodMoon)
	{
		OnBloodMoonStarted.Broadcast();
	}
	else if (!bIsBloodMoon && bWasBloodMoon)
	{
		OnBloodMoonEnded.Broadcast();
	}
}

void UHCWeatherSubsystem::ForceWeather(EHCWeatherType NewWeather, float HoldSeconds)
{
	SetWeather(NewWeather);
	ForcedHoldRemaining = FMath::Max(0.f, HoldSeconds);
}

void UHCWeatherSubsystem::ScheduleNextTransition()
{
	// Randomize around the average so transitions don't feel metronomic.
	TimeUntilNextTransition = FMath::FRandRange(AverageTransitionInterval * 0.6f, AverageTransitionInterval * 1.4f);
}

EHCWeatherType UHCWeatherSubsystem::PickNextWeather() const
{
	// Blood Moon is rare; corruption raises its odds. Otherwise the Moors lean fog/rain.
	const float BloodMoonChance = 0.03f + CorruptionInfluence * 0.22f;
	if (FMath::FRand() < BloodMoonChance)
	{
		return EHCWeatherType::BloodMoon;
	}

	static const TArray<TPair<EHCWeatherType, float>> Weights = {
		{ EHCWeatherType::Fog,          0.35f },
		{ EHCWeatherType::Rain,         0.25f },
		{ EHCWeatherType::Clear,        0.20f },
		{ EHCWeatherType::StrongWind,   0.12f },
		{ EHCWeatherType::Thunderstorm, 0.08f }
	};

	float Total = 0.f;
	for (const auto& Pair : Weights) { Total += Pair.Value; }

	float Roll = FMath::FRand() * Total;
	for (const auto& Pair : Weights)
	{
		Roll -= Pair.Value;
		if (Roll <= 0.f && Pair.Key != CurrentWeather)
		{
			return Pair.Key;
		}
	}
	return EHCWeatherType::Fog;
}
