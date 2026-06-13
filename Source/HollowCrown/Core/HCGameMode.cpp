// Copyright Hollow Crown Studio. All Rights Reserved.

#include "Core/HCGameMode.h"
#include "Player/HCCharacter.h"
#include "Player/HCPlayerController.h"

AHCGameMode::AHCGameMode()
{
	DefaultPawnClass = AHCCharacter::StaticClass();
	PlayerControllerClass = AHCPlayerController::StaticClass();
}
