// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HCPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class AHCCharacter;

/**
 * Wires Enhanced Input to the player character's intent functions. Input Actions and the
 * Input Mapping Context are assigned in a Blueprint subclass; the control scheme is
 * documented in Config/DefaultInput.ini.
 */
UCLASS()
class HOLLOWCROWN_API AHCPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Input")
	TObjectPtr<UInputAction> LightAttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Input")
	TObjectPtr<UInputAction> HeavyAttackAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Input")
	TObjectPtr<UInputAction> BlockAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Input")
	TObjectPtr<UInputAction> DodgeAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Input")
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Hollow Crown|Input")
	TObjectPtr<UInputAction> InteractAction;

private:
	AHCCharacter* GetHCCharacter() const;

	void OnMove(const FInputActionValue& Value);
	void OnLook(const FInputActionValue& Value);
	void OnLightAttack(const FInputActionValue& Value);
	void OnHeavyAttack(const FInputActionValue& Value);
	void OnBlockStarted(const FInputActionValue& Value);
	void OnBlockCompleted(const FInputActionValue& Value);
	void OnDodge(const FInputActionValue& Value);
	void OnSprintStarted(const FInputActionValue& Value);
	void OnSprintCompleted(const FInputActionValue& Value);
	void OnInteract(const FInputActionValue& Value);
};
