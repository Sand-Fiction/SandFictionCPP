// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SF_InventoryComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "SF_RecipeBookComponent.generated.h"

// ToDo: REWRITE THIS INTO A GAMEINSTANCE SUBSYSTEM!!! (for better SaveData Handling)

UENUM(BlueprintType)
enum class ECraftingCategory : uint8
{
	Basics,
	Furniture,
	Decorations
};

USTRUCT(BlueprintType)
struct FCraftingRecipe : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag Identifier;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Icon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> ItemClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FInventoryData> RecipeData;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<ECraftingCategory> CraftingCategory;

	bool operator==(const FCraftingRecipe& Other) const
	{
		return Name == Other.Name;
	}

	bool operator==(const FGameplayTag& Other) const
	{
		return Identifier == Other;
	}

	bool IsValid() const
	{
		return RecipeData.Num() > 0;
	}

	FCraftingRecipe()
	{
		Name = FName("RecipeName");
		Description = FText::FromString(TEXT("Here goes the Item Description..."));
		Icon = nullptr;
		ItemClass = nullptr;
		CraftingCategory.AddUnique(ECraftingCategory::Basics);
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRecipeEvent, FCraftingRecipe, Recipe);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDFICTIONCPP_API USF_RecipeBookComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USF_RecipeBookComponent();

	UFUNCTION(BlueprintCallable)
	void AddRecipe(const FGameplayTag Recipe);

	UPROPERTY(BlueprintAssignable)
	FRecipeEvent OnRecipeAdded;

	UFUNCTION(BlueprintCallable)
	void RemoveRecipe(const FGameplayTag RecipeTag);

	UPROPERTY(BlueprintAssignable)
	FRecipeEvent OnRecipeRemoved;

	UFUNCTION(BlueprintCallable)
	bool HasRecipe(const FGameplayTag RecipeTag) const;

	UFUNCTION(BlueprintPure)
	bool HasRecipeItems(const FGameplayTag& RecipeTag) const;

	UFUNCTION(BlueprintPure)
	bool GetRecipeDataByTag(const FGameplayTag& RecipeTag, FCraftingRecipe& RecipeData) const;

protected:

	UFUNCTION()
	void CheckRecipeUnlock(FInventoryData ItemData);

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayTag> KnownRecipes;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* RecipeDataTable;

};
