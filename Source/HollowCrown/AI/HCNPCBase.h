// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HCNPCBase.generated.h"

class UHCAttributeComponent;
class UHCScheduleComponent;

/**
 * Base class for living NPCs (villagers, and the foundation for enemies/bosses). Assembles
 * the shared components and exposes simple hooks the Behavior Tree and game systems drive.
 * See Docs/Systems/NPCSystem.md.
 */
UCLASS()
class HOLLOWCROWN_API AHCNPCBase : public ACharacter
{
	GENERATED_BODY()

public:
	AHCNPCBase();

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|NPC")
	UHCScheduleComponent* GetSchedule() const { return Schedule; }

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|NPC")
	UHCAttributeComponent* GetAttributes() const { return Attributes; }

protected:
	virtual void BeginPlay() override;

	/** Vitals (NPCs that fight use poise/stagger like the player). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hollow Crown|NPC")
	TObjectPtr<UHCAttributeComponent> Attributes;

	/** Daily routine + fear/reaction director. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hollow Crown|NPC")
	TObjectPtr<UHCScheduleComponent> Schedule;

	/** Display identity (a full implementation pulls these from a UHCNPCProfile asset). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hollow Crown|NPC")
	FText NPCName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hollow Crown|NPC")
	int32 Age = 30;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Hollow Crown|NPC")
	FName Occupation = NAME_None;

private:
	UFUNCTION()
	void HandleDeath(AActor* Killer);
};
