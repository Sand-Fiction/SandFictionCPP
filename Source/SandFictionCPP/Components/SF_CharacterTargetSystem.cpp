// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/Vector.h"
#include "SandFictionCPP/Components/SF_CharacterTargetComponent.h"
#include "SF_CharacterTargetSystem.h"

// Sets default values for this component's properties
USF_CharacterTargetSystem::USF_CharacterTargetSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USF_CharacterTargetSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USF_CharacterTargetSystem::RegisterTargetComponent(USF_CharacterTargetComponent* TargetComponent)
{
	TargetComponents.AddUnique(TargetComponent);
}


void USF_CharacterTargetSystem::UnRegisterTargetComponent(USF_CharacterTargetComponent* TargetComponent)
{
	TargetComponents.Remove(TargetComponent);
}

void USF_CharacterTargetSystem::LockOn()
{
	if (IsLockedOn == false)
	{
		if (TargetComponents.Num() > 0)
		{
			float DistanceToSystem = MaxLockOnDistance;
			USF_CharacterTargetComponent* NewCurrentTarget = nullptr;

			// Iterate through all registered Targets and find closest one
			for (const auto TargetComponent : TargetComponents)
			{
				const auto SystemLocation = this->GetOwner()->GetActorLocation();
				const auto TargetLocation = TargetComponent->GetComponentLocation();
				const float NewDistanceToSystem = FVector::Distance(SystemLocation, TargetLocation);

				if (NewDistanceToSystem < DistanceToSystem)
				{
					DistanceToSystem = NewDistanceToSystem;
					NewCurrentTarget = TargetComponent;
				}
			}

			// Set the new Current Target
			CurrentTarget = NewCurrentTarget;
			IsLockedOn = true;
		}
	}
}

void USF_CharacterTargetSystem::LockOff()
{
	if (IsLockedOn == true)
	{
		IsLockedOn = false;
		CurrentTarget = nullptr;
	}
}
