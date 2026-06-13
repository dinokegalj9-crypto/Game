// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HCGameInstance.generated.h"

/**
 * Game instance: persists across level loads and is the natural owner of game-instance
 * subsystems such as the save system. Tracks lightweight session-wide state (e.g. the
 * active save slot and accumulated playtime).
 */
UCLASS()
class HOLLOWCROWN_API UHCGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown")
	void SetActiveSaveSlot(const FString& Slot) { ActiveSaveSlot = Slot; }

	UFUNCTION(BlueprintPure, Category = "Hollow Crown")
	const FString& GetActiveSaveSlot() const { return ActiveSaveSlot; }

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Hollow Crown")
	FString ActiveSaveSlot = TEXT("Slot0");
};
