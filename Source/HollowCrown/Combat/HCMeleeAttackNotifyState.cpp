// Copyright Hollow Crown Studio. All Rights Reserved.

#include "Combat/HCMeleeAttackNotifyState.h"
#include "Combat/HCCombatComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"

void UHCMeleeAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		if (AActor* Owner = MeshComp->GetOwner())
		{
			if (UHCCombatComponent* Combat = Owner->FindComponentByClass<UHCCombatComponent>())
			{
				Combat->OnAttackWindowOpen();
			}
		}
	}
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void UHCMeleeAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp)
	{
		if (AActor* Owner = MeshComp->GetOwner())
		{
			if (UHCCombatComponent* Combat = Owner->FindComponentByClass<UHCCombatComponent>())
			{
				Combat->OnAttackWindowClose();
			}
		}
	}
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}

FString UHCMeleeAttackNotifyState::GetNotifyName_Implementation() const
{
	return TEXT("HC Attack Window");
}
