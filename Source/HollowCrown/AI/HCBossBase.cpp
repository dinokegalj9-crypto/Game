// Copyright Hollow Crown Studio. All Rights Reserved.

#include "AI/HCBossBase.h"
#include "AI/HCBossDefinition.h"
#include "Stats/HCAttributeComponent.h"
#include "Corruption/HCCorruptionComponent.h"
#include "Core/HCWorldStateSubsystem.h"
#include "HollowCrown.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"

AHCBossBase::AHCBossBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AHCBossBase::BeginPlay()
{
	Super::BeginPlay();

	// Bind to our own death to drive the world-change pipeline. AHCNPCBase also binds
	// HandleDeath for the generic NPC behavior; both run independently.
	if (UHCAttributeComponent* Attr = GetAttributes())
	{
		Attr->OnDeath.AddDynamic(this, &AHCBossBase::HandleBossDeath);
	}
}

void AHCBossBase::HandleBossDeath(AActor* Killer)
{
	if (bDefeated)
	{
		return;
	}
	bDefeated = true;
	ExecuteDeathConsequences(Killer);
	OnDefeatedPresentation();
	OnBossDefeatedActor.Broadcast(this);
}

void AHCBossBase::ExecuteDeathConsequences(AActor* Killer)
{
	if (!BossDefinition || !BossDefinition->BossId.IsValid())
	{
		UE_LOG(LogHollowCrown, Warning, TEXT("Boss %s has no valid BossDefinition; skipping consequences."), *GetName());
		return;
	}

	// (3) Advance corruption + (2) grant ability — applied to the killer if it's the player.
	AActor* AbilityTarget = Killer;
	if (!AbilityTarget)
	{
		if (UWorld* World = GetWorld())
		{
			if (APlayerController* PC = World->GetFirstPlayerController())
			{
				AbilityTarget = PC->GetPawn();
			}
		}
	}

	if (AbilityTarget)
	{
		if (UHCCorruptionComponent* Corruption = AbilityTarget->FindComponentByClass<UHCCorruptionComponent>())
		{
			Corruption->AddCorruption(BossDefinition->CorruptionReward);
		}
		// Ability granting is handled by the ability system (GAS migration on the roadmap);
		// the id is carried on the definition so that layer can read it here.
		UE_LOG(LogHollowCrown, Log, TEXT("Granted ability '%s' from boss '%s'."),
			*BossDefinition->GrantedAbilityId.ToString(), *BossDefinition->BossId.Id.ToString());
	}

	// (1) Change the world + (4) unlock areas — routed through the world-state hub.
	if (UWorld* World = GetWorld())
	{
		if (UHCWorldStateSubsystem* WorldState = World->GetSubsystem<UHCWorldStateSubsystem>())
		{
			WorldState->ReportBossDefeated(BossDefinition->BossId, BossDefinition->RegionsToUnlock);
		}
	}
}
