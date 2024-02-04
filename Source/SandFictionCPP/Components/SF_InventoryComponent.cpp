// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_InventoryComponent.h"

// Sets default values for this component's properties
USF_InventoryComponent::USF_InventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USF_InventoryComponent::AddItemToInventory(const FInventoryData ItemDataToAdd)
{
	CurrentInventory.Add(ItemDataToAdd);
	RestackInventory();
	OnItemAddedToInventory.Broadcast(ItemDataToAdd);
}

bool USF_InventoryComponent::HasItemInInventory(const FInventoryData& InventoryData) const
{
	return CurrentInventory.Contains(InventoryData);
}

TArray<FInventoryData> USF_InventoryComponent::GetInventory() const
{
	return CurrentInventory;
}

FItemData USF_InventoryComponent::GetItemDataByInventoryData(FInventoryData InventoryData, bool &Valid) const
{
	if (ItemDataTable && !InventoryData.ItemData.IsNull())
	{
		if (const auto ItemData = ItemDataTable->FindRow<FItemData>(InventoryData.ItemData.RowName, ""))
		{
			Valid = true;
			return *ItemData;
		}
	}

	Valid = false;
	return FItemData();
}

void USF_InventoryComponent::SortInventory()
{
	RestackInventory();
}

void USF_InventoryComponent::RestackInventory()
{
	TArray<FInventoryData> RestackedInventory;

	// Loop through all Inventory Items
	for (FInventoryData InventoryItem : CurrentInventory)
	{		
		int32 StackIndex = -1;
		
		// Check if there is a stack of the same type in the restacked Inventory
		for (FInventoryData StackedItem: RestackedInventory)
		{
			// save StackIndex
			if (StackedItem.IsSameType(InventoryItem))
			{
				StackIndex = RestackedInventory.Find(StackedItem);
				break;
			}
		}

		// if Stack was found, combine Quantity
		if (StackIndex>=0)
		{
			RestackedInventory[StackIndex].Quantity = RestackedInventory[StackIndex].Quantity + InventoryItem.Quantity;
		}
		// if no stack of the same type was found, add this item to the restacked inventory
		else
		{
			RestackedInventory.Add(InventoryItem);
		}
	}
	CurrentInventory = RestackedInventory;
}

// Called when the game starts
void USF_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USF_InventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

