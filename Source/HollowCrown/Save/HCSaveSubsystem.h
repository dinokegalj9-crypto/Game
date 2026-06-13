// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "HCSaveSubsystem.generated.h"

class UHCSaveGame;

UENUM(BlueprintType)
enum class EHCSaveError : uint8
{
	None          UMETA(DisplayName = "None"),
	NoPlayer      UMETA(DisplayName = "No Player"),
	SlotNotFound  UMETA(DisplayName = "Slot Not Found"),
	VersionTooNew UMETA(DisplayName = "Save Version Too New"),
	WriteFailed   UMETA(DisplayName = "Write Failed")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnGameSaved, const FString&, Slot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnGameLoaded, const FString&, Slot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHCOnSaveError, EHCSaveError, Error);

/**
 * Orchestrates save/load. Gathers state from the world-state and settlement subsystems and
 * the player's components into a UHCSaveGame, and distributes it back on load. Individual
 * systems own their Capture/Restore shape; this subsystem is the conductor.
 * See Docs/Systems/SaveSystem.md.
 */
UCLASS()
class HOLLOWCROWN_API UHCSaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Save")
	bool SaveGame(const FString& Slot);

	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Save")
	bool LoadGame(const FString& Slot);

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Save")
	bool DoesSaveExist(const FString& Slot) const;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Save")
	FHCOnGameSaved OnGameSaved;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Save")
	FHCOnGameLoaded OnGameLoaded;

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Save")
	FHCOnSaveError OnSaveError;

private:
	/** Highest SaveVersion this build understands. */
	static constexpr int32 CurrentSaveVersion = 1;

	/** Collect live state into a new save object. Returns nullptr (and reports) on failure. */
	UHCSaveGame* CaptureWorld();

	/** Push a loaded save object's state back into the live world. */
	void RestoreWorld(UHCSaveGame* Save);
};
