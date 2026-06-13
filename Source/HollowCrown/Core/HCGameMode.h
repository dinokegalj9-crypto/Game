// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "HCGameMode.generated.h"

/**
 * Default game mode for The Hollow Crown. Sets the player character and controller as the
 * defaults; rules and pacing logic attach here as the slice grows.
 */
UCLASS()
class HOLLOWCROWN_API AHCGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHCGameMode();
};
