// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_BuildingComponent.h"

#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "SandFictionCPP/Actors/Items/SF_BuildActor.h"
#include "SandFictionCPP/Character/SF_Character.h"
#include "SandFictionCPP/Core/Subsystems/Room/SFRoomActor.h"
#include "SandFictionCPP/Core/Subsystems/Room/SFRoomSystem.h"

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

bool USF_BuildingComponent::IsInBuildingMode() const
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
	FGameplayTag InRoom;

	//ToDo: Tell Room that it got a new Actor!

	if (FindBuildLocation(Location, InRoom))
	{
		if (GetOwner())
		{
			if (const auto Character = Cast<ASF_Character>(GetOwner()))
			{
				const float AnimDuration = Character->PlayAnimMontage(BuildAnimMontage);
				FTimerHandle TimerHandle;
				GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USF_BuildingComponent::OnBuildAnimFinished, AnimDuration);
			}
		}
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

bool USF_BuildingComponent::FindBuildLocation(FVector& BuildLocation, FGameplayTag& InsideRoom) const
{
	if (!GetWorld() || !GetOwner())
	{
		return false;
	}

	//ToDo: No simple LineTrace but rather an ActorBoundsCollisionCheck
	FHitResult HitResult;
	const FVector StartLocation = GetOwner()->GetActorForwardVector() * 250.f + GetOwner()->GetActorLocation();
	const FVector EndLocation = StartLocation - FVector(0.f, 0.f, 150.f);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_WorldStatic))
	{
		//ToDo: Tell Room that it is now inside of it!
		if (const auto RoomSystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<USFRoomSystem>())
		{
			FSFRoomStruct RoomData;
			if (RoomSystem->GetRoomDataByTag(RoomSystem->CurrentRoom, RoomData))
			{
				// Return false if you are in a Room but Build Limit is reached!
				//ToDo: Proper Warning?
				int32 FreeSpace;
				if (RoomData.IsBuildLimitReached(FreeSpace))
				{
					return false;
				}

				if (const auto RoomActor = Cast<ASFRoomActor>(RoomData.ActorSoftReference.LoadSynchronous()))
				{
					//ToDo: CurrentBuildActor Bounds are probably wrong since it is attached to the Character
					//ToDo: We need to check the BoundingBox of the Preview though
					//ToDo: So the PreviewLocation should be the ActorLocation and only the Miniature should be attached to the Character
					if (RoomActor->IsActorInsideRoom(CurrentBuildActor))
					{
						InsideRoom = RoomData.RoomIdentifier;
					}
				}
			}
		}

		BuildLocation = HitResult.Location;
		return true;
	}

	return false;
}

void USF_BuildingComponent::OnBuildAnimFinished()
{
	FVector Location;
	FGameplayTag InRoom;
	if (FindBuildLocation(Location, InRoom))
	{
		if (const auto RoomSystem = UGameplayStatics::GetGameInstance(this)->GetSubsystem<USFRoomSystem>())
		{
			FTransform Transform;
			Transform.SetLocation(Location);

			const FSFRoomActorStruct NewActor = FSFRoomActorStruct(CurrentBuildActor->Identifier, Transform, CurrentBuildActor->GetClass(), CurrentBuildActor);
			if (RoomSystem->AddActorToRoom(InRoom, NewActor))
			{
				const auto DetachmentRules = FDetachmentTransformRules(EDetachmentRule::KeepWorld, false);
				CurrentBuildActor->DetachFromActor(DetachmentRules);
				CurrentBuildActor->SetActorTransform(Transform);
				CurrentBuildActor->Room = InRoom;
				CurrentBuildActor->OnBuild();
				EndBuildingMode();
			}
		}
	}
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
	FGameplayTag InRoom;
	if (FindBuildLocation(Location, InRoom))
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
