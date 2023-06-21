// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SF_InventoryComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "SF_RecipeBookComponent.generated.h"

USTRUCT(BlueprintType)
struct FCraftingRecipe : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FName Name;

	UPROPERTY(BlueprintReadOnly)
	UTexture2D* Icon;

	UPROPERTY(BlueprintReadOnly)
	TArray<FInventoryData> RecipeData;

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
		Icon = nullptr;
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
