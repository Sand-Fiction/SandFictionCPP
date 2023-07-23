// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_BuildingComponent.h"

#include "EnhancedInputSubsystems.h"
#include "SandFictionCPP/Actors/Items/SF_BuildActor.h"
#include "SandFictionCPP/Character/SF_Character.h"

// Sets default values for this component's properties
USF_BuildingComponent::USF_BuildingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void USF_BuildingComponent::ToggleBuildingMode()
{
	IsInBuildingMode() ? EndBuildingMode() : StartBuildingMode();
}

void USF_BuildingComponent::StartBuildingMode()
{
	const auto OwningCharacter = Cast<ASF_Character>(GetOwner());
	if (!OwningCharacter)
	{
		return;
	}

	OwningCharacter->PlayAnimMontage(PickUpAnimMontage);

	const auto PlayerController = Cast<APlayerController>(OwningCharacter->GetController());
	if (!PlayerController)
	{
		return;
	}

	// Get Input Subsystem and add Building MappingContext
	if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(InputMappingContext, 1);
		bBuildingModeEnabled = true;
		OnBuildModeStart.Broadcast();
	}
}

void USF_BuildingComponent::EndBuildingMode()
{
	const auto OwningCharacter = Cast<ASF_Character>(GetOwner());
	if (!OwningCharacter)
	{
		return;
	}

	const auto PlayerController = Cast<APlayerController>(OwningCharacter->GetController());
	if (!PlayerController)
	{
		return;
	}

	// Get Input Subsystem and add Building MappingContext
	if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
	{
		Subsystem->RemoveMappingContext(InputMappingContext);
		bBuildingModeEnabled = false;
		CurrentBuildActor = nullptr;
		OnBuildModeEnd.Broadcast();
	}
}

bool USF_BuildingComponent::IsInBuildingMode()
{
	return bBuildingModeEnabled;
}

void USF_BuildingComponent::SetBuildActor(ASF_BuildActor* Actor)
{
	CurrentBuildActor = Actor;
}

void USF_BuildingComponent::BuildActor()
{
	FVector Location;
	if (FindBuildLocation(Location))
	{
		const auto DetachmentRules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, false);
		CurrentBuildActor->DetachFromActor(DetachmentRules);

		FTransform Transform;
		Transform.SetLocation(Location);
		CurrentBuildActor->SetActorTransform(Transform);
		CurrentBuildActor->OnBuild();

		//ToDo: TellBuildActor to do stuff (VFX, Anims etc...)

		if (GetOwner())
		{
			if (const auto Character = Cast<ASF_Character>(GetOwner()))
			{
				Character->PlayAnimMontage(BuildAnimMontage);
			}
		}

		EndBuildingMode();
	}
	else
	{
		//ToDo: FailBuild();
	}
}

// Called when the game starts
void USF_BuildingComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool USF_BuildingComponent::FindBuildLocation(FVector& BuildLocation) const
{
	if (!GetWorld() || !GetOwner())
	{
		return false;
	}

	//ToDo: No simple LineTrace but rather an ActorBoundsCollisionCheck
	FHitResult HitResult;
	const FVector StartLocation = GetOwner()->GetActorForwardVector() * 200.f + GetOwner()->GetActorLocation();
	const FVector EndLocation = StartLocation - FVector(0.f, 0.f, 150.f);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_WorldStatic))
	{
		BuildLocation = HitResult.Location;
		return true;
	}

	return false;
}

// Called every frame
void USF_BuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CurrentBuildActor)
	{
		return;
	}

	FVector Location;
	if (FindBuildLocation(Location))
	{
		CurrentBuildActor->SetPreviewLocation(Location);
		CurrentBuildActor->SetPreviewMID(true);
	}
	else
	{
		const auto DefaultLocation = GetOwner()->GetActorForwardVector() * 200.f + GetOwner()->GetActorLocation();
		CurrentBuildActor->SetPreviewLocation(Location);
		CurrentBuildActor->SetPreviewMID(false);
	}
}

