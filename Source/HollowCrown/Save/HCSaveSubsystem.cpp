// Copyright Hollow Crown Studio. All Rights Reserved.

#include "Save/HCSaveSubsystem.h"
#include "Save/HCSaveGame.h"
#include "Core/HCWorldStateSubsystem.h"
#include "Corruption/HCCorruptionComponent.h"
#include "Inventory/HCInventoryComponent.h"
#include "Settlement/HCSettlementSubsystem.h"
#include "HollowCrown.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"

bool UHCSaveSubsystem::DoesSaveExist(const FString& Slot) const
{
	return UGameplayStatics::DoesSaveGameExist(Slot, 0);
}

bool UHCSaveSubsystem::SaveGame(const FString& Slot)
{
	UHCSaveGame* Save = CaptureWorld();
	if (!Save)
	{
		return false; // CaptureWorld already reported the specific error.
	}

	if (!UGameplayStatics::SaveGameToSlot(Save, Slot, 0))
	{
		OnSaveError.Broadcast(EHCSaveError::WriteFailed);
		return false;
	}

	UE_LOG(LogHollowCrown, Log, TEXT("Saved game to slot '%s'."), *Slot);
	OnGameSaved.Broadcast(Slot);
	return true;
}

bool UHCSaveSubsystem::LoadGame(const FString& Slot)
{
	if (!DoesSaveExist(Slot))
	{
		OnSaveError.Broadcast(EHCSaveError::SlotNotFound);
		return false;
	}

	UHCSaveGame* Save = Cast<UHCSaveGame>(UGameplayStatics::LoadGameFromSlot(Slot, 0));
	if (!Save)
	{
		OnSaveError.Broadcast(EHCSaveError::SlotNotFound);
		return false;
	}

	if (Save->SaveVersion > CurrentSaveVersion)
	{
		OnSaveError.Broadcast(EHCSaveError::VersionTooNew);
		return false;
	}
	// Older versions would be migrated forward here as the shape evolves.

	RestoreWorld(Save);
	UE_LOG(LogHollowCrown, Log, TEXT("Loaded game from slot '%s'."), *Slot);
	OnGameLoaded.Broadcast(Slot);
	return true;
}

UHCSaveGame* UHCSaveSubsystem::CaptureWorld()
{
	UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr;
	APlayerController* PC = World ? World->GetFirstPlayerController() : nullptr;
	APawn* Player = PC ? PC->GetPawn() : nullptr;
	if (!Player)
	{
		OnSaveError.Broadcast(EHCSaveError::NoPlayer);
		return nullptr;
	}

	UHCSaveGame* Save = Cast<UHCSaveGame>(UGameplayStatics::CreateSaveGameObject(UHCSaveGame::StaticClass()));
	Save->SaveVersion = CurrentSaveVersion;
	Save->Timestamp = FDateTime::UtcNow();

	// World state.
	if (UHCWorldStateSubsystem* WorldState = World->GetSubsystem<UHCWorldStateSubsystem>())
	{
		WorldState->CaptureState(Save->DefeatedBosses, Save->UnlockedRegions, Save->ChoiceFlags);
	}

	// Player.
	Save->PlayerTransform = Player->GetActorTransform();
	if (UHCCorruptionComponent* Corruption = Player->FindComponentByClass<UHCCorruptionComponent>())
	{
		Save->Corruption = Corruption->CaptureState();
	}
	if (UHCInventoryComponent* Inventory = Player->FindComponentByClass<UHCInventoryComponent>())
	{
		Save->Inventory = Inventory->CaptureState();
	}

	// Settlement.
	if (UHCSettlementSubsystem* Settlement = World->GetSubsystem<UHCSettlementSubsystem>())
	{
		Save->SettlementProsperity = Settlement->GetProsperity();
	}

	return Save;
}

void UHCSaveSubsystem::RestoreWorld(UHCSaveGame* Save)
{
	UWorld* World = GetGameInstance() ? GetGameInstance()->GetWorld() : nullptr;
	if (!World || !Save)
	{
		return;
	}

	if (UHCWorldStateSubsystem* WorldState = World->GetSubsystem<UHCWorldStateSubsystem>())
	{
		WorldState->RestoreState(Save->DefeatedBosses, Save->UnlockedRegions, Save->ChoiceFlags);
	}

	if (APlayerController* PC = World->GetFirstPlayerController())
	{
		if (APawn* Player = PC->GetPawn())
		{
			Player->SetActorTransform(Save->PlayerTransform);
			if (UHCCorruptionComponent* Corruption = Player->FindComponentByClass<UHCCorruptionComponent>())
			{
				Corruption->RestoreState(Save->Corruption);
			}
			if (UHCInventoryComponent* Inventory = Player->FindComponentByClass<UHCInventoryComponent>())
			{
				Inventory->RestoreState(Save->Inventory);
			}
		}
	}
}
