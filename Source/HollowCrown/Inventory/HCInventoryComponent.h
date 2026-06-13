// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "Inventory/HCItemDefinition.h"
#include "HCInventoryComponent.generated.h"

/** A crafting recipe row: inputs -> output, optionally requiring a station. */
USTRUCT(BlueprintType)
struct FHCCraftingRecipe : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	TArray<FHCItemStack> Inputs;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	FHCItemStack Output;

	/** e.g. "Campfire", "Blacksmith". None means craftable anywhere (by hand). */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Recipe")
	FName RequiredStation = NAME_None;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHCOnInventoryChanged);

/**
 * Stack-based inventory with simple crafting. Holds FHCItemStacks and consumes/produces
 * them according to FHCCraftingRecipe rows. See Docs/Systems/SurvivalSystem.md and the
 * crafting notes in the Architecture doc.
 */
UCLASS(ClassGroup = (HollowCrown), meta = (BlueprintSpawnableComponent))
class HOLLOWCROWN_API UHCInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UHCInventoryComponent();

	/** Adds items, merging into existing stacks up to MaxStackSize. Returns the number that did not fit. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Inventory")
	int32 AddItem(UHCItemDefinition* Item, int32 Quantity);

	/** Removes up to Quantity of an item. Returns the number actually removed. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Inventory")
	int32 RemoveItem(UHCItemDefinition* Item, int32 Quantity);

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Inventory")
	int32 GetItemCount(UHCItemDefinition* Item) const;

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Inventory")
	bool HasItems(const TArray<FHCItemStack>& Required) const;

	/** Attempts to craft a recipe given the available station. Returns true on success. */
	UFUNCTION(BlueprintCallable, Category = "Hollow Crown|Inventory")
	bool Craft(const FHCCraftingRecipe& Recipe, FName AvailableStation);

	UFUNCTION(BlueprintPure, Category = "Hollow Crown|Inventory")
	const TArray<FHCItemStack>& GetStacks() const { return Stacks; }

	UPROPERTY(BlueprintAssignable, Category = "Hollow Crown|Inventory")
	FHCOnInventoryChanged OnInventoryChanged;

	// --- Save support ---
	const TArray<FHCItemStack>& CaptureState() const { return Stacks; }
	void RestoreState(const TArray<FHCItemStack>& InStacks);

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Hollow Crown|Inventory")
	TArray<FHCItemStack> Stacks;
};
