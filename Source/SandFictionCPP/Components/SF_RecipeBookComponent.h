// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SF_InventoryComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "SF_RecipeBookComponent.generated.h"

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


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDFICTIONCPP_API USF_RecipeBookComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USF_RecipeBookComponent();

	UFUNCTION(BlueprintCallable)
	void AddRecipe(const FCraftingRecipe Recipe);

	UFUNCTION(BlueprintCallable)
	void RemoveRecipe(const FCraftingRecipe Recipe);

	UFUNCTION(BlueprintCallable)
	bool HasRecipe(const FDataTableRowHandle RecipeData) const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TArray<FCraftingRecipe> KnownRecipes;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* RecipeDataTable;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
