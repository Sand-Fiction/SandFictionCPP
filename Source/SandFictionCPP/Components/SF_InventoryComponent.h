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

	UPROPERTY(BlueprintReadWrite)
	FName Name;

	UPROPERTY(BlueprintReadWrite)
	FText Description;

	UPROPERTY(BlueprintReadWrite)
	int32 MaxStackSize;

	UPROPERTY(BlueprintReadWrite)
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

	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle ItemData;

	UPROPERTY(BlueprintReadWrite)
	int32 Quantity;

	FInventoryData()
	{
		ItemData = FDataTableRowHandle();
		Quantity = 0;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SANDFICTIONCPP_API USF_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USF_InventoryComponent();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UDataTable* ItemDataTable;

	UPROPERTY()
	TArray<FInventoryData> CurrentInventory;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
