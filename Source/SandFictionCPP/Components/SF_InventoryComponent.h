// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "SF_InventoryComponent.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStackSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Icon;

	FItemData()
	{
		Name = FName("Unnamed Item");
		Description = FText::FromString("Missing Description");
		MaxStackSize = 1;
		Icon = nullptr;
	}
};

USTRUCT(BlueprintType)
struct FInventoryData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FDataTableRowHandle ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Quantity;

	// Override the equality operator
	bool operator==(const FInventoryData& Other) const
	{
		return (ItemData == Other.ItemData) && (Quantity == Other.Quantity);
	}

	bool IsSameType(const FInventoryData& Other) const
	{
		return ItemData == Other.ItemData;
	}

	FInventoryData()
	{
		ItemData = FDataTableRowHandle();
		Quantity = 0;
	}
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemAddedToInventory, FInventoryData, ItemData);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDFICTIONCPP_API USF_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USF_InventoryComponent();

	UFUNCTION(BlueprintCallable)
	void AddItemToInventory(FInventoryData ItemDataToAdd);

	UFUNCTION(BlueprintPure)
	bool HasItemInInventory(const FInventoryData& InventoryData) const;

	UFUNCTION(BlueprintPure)
	TArray<FInventoryData> GetInventory() const;

	UFUNCTION(BlueprintPure)
	FItemData GetItemDataByInventoryData(FInventoryData InventoryData, bool &Valid) const;

	UFUNCTION(BlueprintCallable)
	void SortInventory();

	UFUNCTION(BlueprintCallable)
	void RestackInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* ItemDataTable;

public:
	UPROPERTY(VisibleAnywhere)
	TArray<FInventoryData> CurrentInventory;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FOnItemAddedToInventory OnItemAddedToInventory;

};
