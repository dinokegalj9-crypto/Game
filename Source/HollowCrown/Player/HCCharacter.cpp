// Copyright Hollow Crown Studio. All Rights Reserved.

#include "Player/HCCharacter.h"
#include "Stats/HCAttributeComponent.h"
#include "Combat/HCCombatComponent.h"
#include "Corruption/HCCorruptionComponent.h"
#include "Survival/HCSurvivalComponent.h"
#include "Inventory/HCInventoryComponent.h"
#include "HollowCrown.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AHCCharacter::AHCCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Camera boom + third-person camera (Bloodborne/Elden-Ring-style framing).
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 350.f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	// Movement: face the direction of travel; controller drives camera yaw.
	bUseControllerRotationYaw = false;
	if (UCharacterMovementComponent* Move = GetCharacterMovement())
	{
		Move->bOrientRotationToMovement = true;
		Move->RotationRate = FRotator(0.f, 540.f, 0.f);
		Move->MaxWalkSpeed = WalkSpeed;
	}

	// Gameplay components.
	Attributes = CreateDefaultSubobject<UHCAttributeComponent>(TEXT("Attributes"));
	Combat     = CreateDefaultSubobject<UHCCombatComponent>(TEXT("Combat"));
	Corruption = CreateDefaultSubobject<UHCCorruptionComponent>(TEXT("Corruption"));
	Survival   = CreateDefaultSubobject<UHCSurvivalComponent>(TEXT("Survival"));
	Inventory  = CreateDefaultSubobject<UHCInventoryComponent>(TEXT("Inventory"));
}

void AHCCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (Corruption)
	{
		Corruption->OnCorruptionStageChanged.AddDynamic(this, &AHCCharacter::HandleCorruptionStageChanged);
	}
}

void AHCCharacter::MoveInput(const FVector2D& Axis)
{
	if (!Controller || Axis.IsNearlyZero())
	{
		return;
	}

	// Move relative to the camera's yaw.
	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(Forward, Axis.Y);
	AddMovementInput(Right, Axis.X);

	if (bSprinting && Attributes)
	{
		// Sprinting costs stamina; if it runs out, drop back to walking.
		const float Cost = SprintStaminaDrainPerSecond * GetWorld()->GetDeltaSeconds();
		if (!Attributes->TrySpendStamina(Cost))
		{
			SetSprinting(false);
		}
	}
}

void AHCCharacter::LookInput(const FVector2D& Axis)
{
	AddControllerYawInput(Axis.X);
	AddControllerPitchInput(Axis.Y);
}

void AHCCharacter::SetSprinting(bool bSprint)
{
	bSprinting = bSprint;
	if (UCharacterMovementComponent* Move = GetCharacterMovement())
	{
		Move->MaxWalkSpeed = bSprint ? SprintSpeed : WalkSpeed;
	}
}

void AHCCharacter::DoLightAttack()   { if (Combat) { Combat->RequestAttack(EHCAttackType::Light); } }
void AHCCharacter::DoHeavyAttack()   { if (Combat) { Combat->RequestAttack(EHCAttackType::Heavy); } }
void AHCCharacter::DoChargedAttack() { if (Combat) { Combat->RequestAttack(EHCAttackType::Charged); } }
void AHCCharacter::StartBlocking()   { if (Combat) { Combat->StartBlock(); } }
void AHCCharacter::StopBlocking()    { if (Combat) { Combat->StopBlock(); } }
void AHCCharacter::DoDodge()         { if (Combat) { Combat->RequestDodge(); } }

void AHCCharacter::DoInteract()
{
	// Interaction tracing/targeting is implemented alongside the interaction system;
	// the input seam exists now so controller bindings are stable.
}

void AHCCharacter::HandleCorruptionStageChanged(EHCCorruptionStage OldStage, EHCCorruptionStage NewStage)
{
	UE_LOG(LogHollowCrown, Log, TEXT("Player corruption stage: %d -> %d"),
		static_cast<int32>(OldStage), static_cast<int32>(NewStage));
	OnCorruptionStageChangedVisual(OldStage, NewStage);
}
