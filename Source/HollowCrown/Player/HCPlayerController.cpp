// Copyright Hollow Crown Studio. All Rights Reserved.

#include "Player/HCPlayerController.h"
#include "Player/HCCharacter.h"
#include "HollowCrown.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"

void AHCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LP = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (DefaultMappingContext)
			{
				Subsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}
}

void AHCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EIC)
	{
		UE_LOG(LogHollowCrown, Warning, TEXT("EnhancedInputComponent missing; check project input settings."));
		return;
	}

	if (MoveAction)        { EIC->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHCPlayerController::OnMove); }
	if (LookAction)        { EIC->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHCPlayerController::OnLook); }
	if (LightAttackAction) { EIC->BindAction(LightAttackAction, ETriggerEvent::Started, this, &AHCPlayerController::OnLightAttack); }
	if (HeavyAttackAction) { EIC->BindAction(HeavyAttackAction, ETriggerEvent::Started, this, &AHCPlayerController::OnHeavyAttack); }
	if (BlockAction)
	{
		EIC->BindAction(BlockAction, ETriggerEvent::Started, this, &AHCPlayerController::OnBlockStarted);
		EIC->BindAction(BlockAction, ETriggerEvent::Completed, this, &AHCPlayerController::OnBlockCompleted);
	}
	if (DodgeAction)   { EIC->BindAction(DodgeAction, ETriggerEvent::Started, this, &AHCPlayerController::OnDodge); }
	if (SprintAction)
	{
		EIC->BindAction(SprintAction, ETriggerEvent::Started, this, &AHCPlayerController::OnSprintStarted);
		EIC->BindAction(SprintAction, ETriggerEvent::Completed, this, &AHCPlayerController::OnSprintCompleted);
	}
	if (InteractAction) { EIC->BindAction(InteractAction, ETriggerEvent::Started, this, &AHCPlayerController::OnInteract); }
}

AHCCharacter* AHCPlayerController::GetHCCharacter() const
{
	return Cast<AHCCharacter>(GetPawn());
}

void AHCPlayerController::OnMove(const FInputActionValue& Value)
{
	if (AHCCharacter* C = GetHCCharacter())
	{
		C->MoveInput(Value.Get<FVector2D>());
	}
}

void AHCPlayerController::OnLook(const FInputActionValue& Value)
{
	if (AHCCharacter* C = GetHCCharacter())
	{
		C->LookInput(Value.Get<FVector2D>());
	}
}

void AHCPlayerController::OnLightAttack(const FInputActionValue& Value)
{
	if (AHCCharacter* C = GetHCCharacter()) { C->DoLightAttack(); }
}

void AHCPlayerController::OnHeavyAttack(const FInputActionValue& Value)
{
	if (AHCCharacter* C = GetHCCharacter()) { C->DoHeavyAttack(); }
}

void AHCPlayerController::OnBlockStarted(const FInputActionValue& Value)
{
	if (AHCCharacter* C = GetHCCharacter()) { C->StartBlocking(); }
}

void AHCPlayerController::OnBlockCompleted(const FInputActionValue& Value)
{
	if (AHCCharacter* C = GetHCCharacter()) { C->StopBlocking(); }
}

void AHCPlayerController::OnDodge(const FInputActionValue& Value)
{
	if (AHCCharacter* C = GetHCCharacter()) { C->DoDodge(); }
}

void AHCPlayerController::OnSprintStarted(const FInputActionValue& Value)
{
	if (AHCCharacter* C = GetHCCharacter()) { C->SetSprinting(true); }
}

void AHCPlayerController::OnSprintCompleted(const FInputActionValue& Value)
{
	if (AHCCharacter* C = GetHCCharacter()) { C->SetSprinting(false); }
}

void AHCPlayerController::OnInteract(const FInputActionValue& Value)
{
	if (AHCCharacter* C = GetHCCharacter()) { C->DoInteract(); }
}
