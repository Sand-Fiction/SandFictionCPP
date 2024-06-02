// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_ScanTargetComponent.h"

#include "SFScanningSystem.h"
#include "Kismet/GameplayStatics.h"
#include "SandFictionCPP/Character/SF_Character_Main.h"
#include "SandFictionCPP/Components/SF_InventoryComponent.h"


// Sets default values for this component's properties
USF_ScanTargetComponent::USF_ScanTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bAutoActivate = true;
	// ...
}

void USF_ScanTargetComponent::Scan()
{
	// Tell ScanningSystem that we scanned this identity
	const auto GameInstance = UGameplayStatics::GetGameInstance(this);
	if (const auto ScanningSystem = GameInstance->GetSubsystem<USFScanningSystem>())
	{
		ScanningSystem->AddScannedIdentity(ScanIdentity);
	}

	// Tell character to add this resource
	if (const auto PlayerCharacter = Cast<ASF_Character_Main>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		FInventoryData ItemData;
		ItemData.Quantity = 1;
		ItemData.ItemData = ResourceData;
		
		PlayerCharacter->GetInventoryComponent()->AddItemToInventory(ItemData);
	}
}

void USF_ScanTargetComponent::Deactivate()
{
	Super::Deactivate();

	UpdateMeshOverlayMaterial(false);
}

void USF_ScanTargetComponent::Activate(bool bReset)
{
	Super::Activate(bReset);
	
	UpdateMeshOverlayMaterial(true);
}

// Called when the game starts
void USF_ScanTargetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateMeshOverlayMaterial(true);

	const auto GameInstance = UGameplayStatics::GetGameInstance(this);
	if (const auto ScanningSystem = GameInstance->GetSubsystem<USFScanningSystem>())
	{
			ScanningSystem->RegisterScanTargetComponent(this);
	}
}

void USF_ScanTargetComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	const auto GameInstance = UGameplayStatics::GetGameInstance(this);
	if (const auto ScanningSystem = GameInstance->GetSubsystem<USFScanningSystem>())
	{
		ScanningSystem->UnRegisterScanTargetComponent(this);
	}
}

void USF_ScanTargetComponent::UpdateMeshOverlayMaterial(const bool bVisible)
{
	if (!GetOwner())
	{
		return;
	}
	
	TArray<UStaticMeshComponent*> StaticMeshes;
	GetOwner()->GetComponents<UStaticMeshComponent>(StaticMeshes);

	UMaterialInterface* OverlayMaterial;
	bVisible ? OverlayMaterial = ScanOverlayMaterial : OverlayMaterial = nullptr;
	
	for (const auto Mesh : StaticMeshes)
	{
		Mesh->SetOverlayMaterial(OverlayMaterial);
	}
}

// Called every frame
void USF_ScanTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

