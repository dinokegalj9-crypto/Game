// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "HCMeleeAttackNotifyState.generated.h"

/**
 * Drives a weapon's "active hit window" from an attack montage. Add this notify state over the
 * frames where the blade should connect: NotifyBegin opens the window (starts the weapon trace),
 * NotifyEnd closes it. This is the sanctioned bridge between animation and the combat component
 * (the only place animation pokes gameplay). See Docs/Systems/CombatSystem.md and Docs/GymSetup.md.
 */
UCLASS(meta = (DisplayName = "HC Melee Attack Window"))
class HOLLOWCROWN_API UHCMeleeAttackNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	virtual FString GetNotifyName_Implementation() const override;
};
