// Fill out your copyright notice in the Description page of Project Settings.

#include "SF_CharacterTargetSystem.h"
#include "Math/Vector.h"
#include "SandFictionCPP/Components/SF_CharacterTargetComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values for this component's properties
USF_CharacterTargetSystem::USF_CharacterTargetSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	

	// ...
}


// Called when the game starts
void USF_CharacterTargetSystem::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false);

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

			if (CurrentTarget != nullptr)
			{
				IsLockedOn = true;
				SpawnWidgetComponent();
				SetComponentTickEnabled(true);
			}
		}
	}
}

void USF_CharacterTargetSystem::LockOff()
{
	if (IsLockedOn == true)
	{
		IsLockedOn = false;
		CurrentTarget = nullptr;
		DestroyWidgetComponent();
		SetComponentTickEnabled(false);
	}
}

void USF_CharacterTargetSystem::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	const auto SystemLocation = this->GetOwner()->GetActorLocation();
	const auto TargetLocation = CurrentTarget->GetComponentLocation();
	const float DistanceToSystem = FVector::Distance(SystemLocation, TargetLocation);

	if (DistanceToSystem > MaxLockOnDistance)
	{
		LockOff();
	}
}

void USF_CharacterTargetSystem::SpawnWidgetComponent()
{
	if (CurrentTarget != nullptr)
	{
		const FTransform SpawnTransform = CurrentTarget->GetRelativeTransform();
		const auto NewComponent = CurrentTarget->GetOwner()->AddComponentByClass(UWidgetComponent::StaticClass(), false, SpawnTransform, false);
		WidgetComponent = Cast<UWidgetComponent>(NewComponent);
		WidgetComponent->SetWidgetClass(WidgetClass);
		WidgetComponent->SetDrawAtDesiredSize(true);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComponent->SetTwoSided(true);
		WidgetComponent->SetCastShadow(false);
	}
}

void USF_CharacterTargetSystem::DestroyWidgetComponent()
{
	if (WidgetComponent != nullptr)
	{
		WidgetComponent->DestroyComponent();
		WidgetComponent = nullptr;
	}
}
