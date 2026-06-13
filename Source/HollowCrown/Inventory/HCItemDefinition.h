// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "HCItemDefinition.generated.h"

class UTexture2D;

UENUM(BlueprintType)
enum class EHCItemType : uint8
{
	Material   UMETA(DisplayName = "Material"),
	Consumable UMETA(DisplayName = "Consumable"),
	Weapon     UMETA(DisplayName = "Weapon"),
	Armor      UMETA(DisplayName = "Armor"),
	Key        UMETA(DisplayName = "Key Item")
};

/** Immutable definition of an item. Stacks reference this; instance state lives in FHCItemStack. */
UCLASS(BlueprintType)
class HOLLOWCROWN_API UHCItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FName ItemId = NAME_None;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (MultiLine = true))
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	EHCItemType ItemType = EHCItemType::Material;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UTexture2D> Icon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	float Weight = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item", meta = (ClampMin = "1"))
	int32 MaxStackSize = 99;

	/** For consumables: how much it restores (food, health, etc.). Interpreted by the user. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	float ConsumableValue = 0.f;
};

/** A quantity of a given item in an inventory. */
USTRUCT(BlueprintType)
struct FHCItemStack
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TObjectPtr<UHCItemDefinition> Item = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 Quantity = 0;

	bool IsValid() const { return Item != nullptr && Quantity > 0; }
};
