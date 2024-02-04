// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_RecipeBookComponent.h"

// Sets default values for this component's properties
USF_RecipeBookComponent::USF_RecipeBookComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USF_RecipeBookComponent::AddRecipe(const FGameplayTag RecipeTag)
{
	// return if Recipe is already learned
	if (HasRecipe(RecipeTag))
	{
		return;
	}
	
	KnownRecipes.AddUnique(RecipeTag);
	FCraftingRecipe RecipeData;
	GetRecipeDataByTag(RecipeTag, RecipeData);
	OnRecipeAdded.Broadcast(RecipeData);
}

void USF_RecipeBookComponent::RemoveRecipe(const FGameplayTag RecipeTag)
{
	// return if Recipe is not learned
	if (!HasRecipe(RecipeTag))
	{
		return;
	}
	
	KnownRecipes.Remove(RecipeTag);
	FCraftingRecipe RecipeData;
	GetRecipeDataByTag(RecipeTag, RecipeData);
	OnRecipeRemoved.Broadcast(RecipeData);
}

bool USF_RecipeBookComponent::HasRecipe(const FGameplayTag RecipeTag) const
{
	return KnownRecipes.Contains(RecipeTag);
}

bool USF_RecipeBookComponent::HasRecipeItems(const FGameplayTag& RecipeTag) const
{
	bool HasItems = false;

	if (GetOwner())
	{
		if (const auto Inventory = Cast<USF_InventoryComponent>(GetOwner()->FindComponentByClass<USF_InventoryComponent>()))
		{
			FCraftingRecipe Recipe;
			GetRecipeDataByTag(RecipeTag, Recipe);

			for (const auto InventoryData : Recipe.RecipeData)
			{
				HasItems = Inventory->HasItemInInventory(InventoryData);

				// No need to check other Items, if already one misses
				if (!HasItems)
				{
					break;
				}
			}
		}
	}
	return HasItems;
}

bool USF_RecipeBookComponent::GetRecipeDataByTag(const FGameplayTag& Recipe, FCraftingRecipe &RecipeData) const
{
	if (!RecipeDataTable)
	{
		return false;
	}

	TArray<FCraftingRecipe*> OutRows;
	RecipeDataTable->GetAllRows<FCraftingRecipe>("", OutRows);

	for (const auto TempRecipeData : OutRows)
	{
		if (TempRecipeData->Identifier == Recipe)
		{
			RecipeData = *TempRecipeData;
			return true;
		}
	}

	return false;
}

void USF_RecipeBookComponent::CheckRecipeUnlock(FInventoryData ItemData)
{
	if (!RecipeDataTable)
	{
		return;
	}

	const auto RowNames = RecipeDataTable->GetRowNames();
	for (const auto RowName : RowNames)
	{
		if (const auto Recipe = RecipeDataTable->FindRow<FCraftingRecipe>(RowName, ""))
		{
			if (HasRecipeItems(Recipe->Identifier))
			{
				AddRecipe(Recipe->Identifier);
			}
		}
	}
}


// Called when the game starts
void USF_RecipeBookComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		if (const auto Inventory = Cast<USF_InventoryComponent>(GetOwner()->FindComponentByClass<USF_InventoryComponent>()))
		{
			Inventory->OnItemAddedToInventory.AddDynamic(this, &USF_RecipeBookComponent::CheckRecipeUnlock);
		}
	}
}

