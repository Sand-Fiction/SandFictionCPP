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

void USF_RecipeBookComponent::AddRecipe(const FCraftingRecipe Recipe)
{
	KnownRecipes.AddUnique(Recipe);
}

void USF_RecipeBookComponent::RemoveRecipe(const FCraftingRecipe Recipe)
{
	KnownRecipes.Remove(Recipe);
}

bool USF_RecipeBookComponent::HasRecipe(const FDataTableRowHandle RecipeData) const
{
	if (RecipeData.DataTable)
	{
		const auto RecipeStruct = RecipeData.DataTable->FindRow<FCraftingRecipe>(RecipeData.RowName, "", false);
		return RecipeStruct->IsValid();
	}

	return false;
}


// Called when the game starts
void USF_RecipeBookComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USF_RecipeBookComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

