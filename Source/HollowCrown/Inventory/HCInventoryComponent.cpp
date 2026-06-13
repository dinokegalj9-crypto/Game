// Copyright Hollow Crown Studio. All Rights Reserved.

#include "Inventory/HCInventoryComponent.h"
#include "HollowCrown.h"

UHCInventoryComponent::UHCInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

int32 UHCInventoryComponent::AddItem(UHCItemDefinition* Item, int32 Quantity)
{
	if (!Item || Quantity <= 0)
	{
		return Quantity;
	}

	int32 Remaining = Quantity;

	// Fill existing stacks first.
	for (FHCItemStack& Stack : Stacks)
	{
		if (Stack.Item == Item && Stack.Quantity < Item->MaxStackSize)
		{
			const int32 Space = Item->MaxStackSize - Stack.Quantity;
			const int32 Added = FMath::Min(Space, Remaining);
			Stack.Quantity += Added;
			Remaining -= Added;
			if (Remaining <= 0)
			{
				break;
			}
		}
	}

	// Spill into new stacks.
	while (Remaining > 0)
	{
		FHCItemStack NewStack;
		NewStack.Item = Item;
		NewStack.Quantity = FMath::Min(Item->MaxStackSize, Remaining);
		Remaining -= NewStack.Quantity;
		Stacks.Add(NewStack);
	}

	OnInventoryChanged.Broadcast();
	return Remaining; // amount that did not fit (0 since we always add new stacks)
}

int32 UHCInventoryComponent::RemoveItem(UHCItemDefinition* Item, int32 Quantity)
{
	if (!Item || Quantity <= 0)
	{
		return 0;
	}

	int32 ToRemove = Quantity;
	for (int32 i = Stacks.Num() - 1; i >= 0 && ToRemove > 0; --i)
	{
		if (Stacks[i].Item != Item)
		{
			continue;
		}
		const int32 Taken = FMath::Min(Stacks[i].Quantity, ToRemove);
		Stacks[i].Quantity -= Taken;
		ToRemove -= Taken;
		if (Stacks[i].Quantity <= 0)
		{
			Stacks.RemoveAt(i);
		}
	}

	const int32 Removed = Quantity - ToRemove;
	if (Removed > 0)
	{
		OnInventoryChanged.Broadcast();
	}
	return Removed;
}

int32 UHCInventoryComponent::GetItemCount(UHCItemDefinition* Item) const
{
	int32 Count = 0;
	for (const FHCItemStack& Stack : Stacks)
	{
		if (Stack.Item == Item)
		{
			Count += Stack.Quantity;
		}
	}
	return Count;
}

bool UHCInventoryComponent::HasItems(const TArray<FHCItemStack>& Required) const
{
	for (const FHCItemStack& Req : Required)
	{
		if (!Req.IsValid() || GetItemCount(Req.Item) < Req.Quantity)
		{
			return false;
		}
	}
	return true;
}

bool UHCInventoryComponent::Craft(const FHCCraftingRecipe& Recipe, FName AvailableStation)
{
	if (!Recipe.RequiredStation.IsNone() && Recipe.RequiredStation != AvailableStation)
	{
		return false;
	}
	if (!HasItems(Recipe.Inputs) || !Recipe.Output.IsValid())
	{
		return false;
	}

	for (const FHCItemStack& Input : Recipe.Inputs)
	{
		RemoveItem(Input.Item, Input.Quantity);
	}
	AddItem(Recipe.Output.Item, Recipe.Output.Quantity);

	UE_LOG(LogHollowCrown, Verbose, TEXT("Crafted %s x%d"),
		*GetNameSafe(Recipe.Output.Item), Recipe.Output.Quantity);
	return true;
}

void UHCInventoryComponent::RestoreState(const TArray<FHCItemStack>& InStacks)
{
	Stacks = InStacks;
	OnInventoryChanged.Broadcast();
}
