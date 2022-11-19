// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_InteractionSystem.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
USF_InteractionSystem::USF_InteractionSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	InteractionDistance = 200.0f;
	IndicatorDistance = 500.0f;
}

void USF_InteractionSystem::RegisterInteractable(USF_InteractableComponent* InteractableComponent)
{
	InteractableComponents.AddUnique(InteractableComponent);
}

void USF_InteractionSystem::UnRegisterInteractable(USF_InteractableComponent* InteractableComponent)
{
	InteractableComponents.Remove(InteractableComponent);
}

void USF_InteractionSystem::Interact()
{
	if (CurrentInteractable)
	{
		CurrentInteractable->OnInteraction.Broadcast();
	}
}

// Set Status of Interactables to Not/InRange and De/Active
void USF_InteractionSystem::CheckInteractables()
{
	if (InteractableComponents.Num() > 0)
	{
		USF_InteractableComponent* ClosestInteractable = nullptr;
		float ClosestDistance = InteractionDistance * 2;

		for (const auto Interactable : InteractableComponents)
		{
			const auto InteractableLocation = Interactable->GetComponentLocation();
			const auto PlayerLocation = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation();
			const auto Distance = UKismetMathLibrary::Vector_Distance(InteractableLocation, PlayerLocation);
			if (Distance <= IndicatorDistance)
			{
				// Set the Interactable to be in Range if not already
				if (!Interactable->GetIsInRange())
				{
					Interactable->SetInRange(true);
				}

				if (Distance <= InteractionDistance)
				{
					if (Distance <= ClosestDistance)
					{
						ClosestInteractable = Interactable;
						ClosestDistance = Distance;
					}
				}
			}
			else
			{
				Interactable->SetInRange(false);
			}
		}

		// Set's Closest Interactable to be Active
		if (ClosestInteractable)
		{
			CurrentInteractable = ClosestInteractable;
			CurrentInteractable->SetIsActive(true);
		}
		else
		{
			CurrentInteractable = nullptr;
		}

		// Set's all InActive Interactables
		for (const auto Interactable : InteractableComponents)
		{
			if (Interactable != CurrentInteractable)
			{
				Interactable->SetIsActive(false);
			}
		}
	}
}

// Called when the game starts
void USF_InteractionSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void USF_InteractionSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckInteractables();
}

