// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_InteractableComponent.h"
#include "SF_InteractionSystem.h"
#include "SF_InteractionWidget.h"
#include "SF_InteractionWidgetComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SandFictionCPP/Character/SF_Character_Main.h"

// Sets default values for this component's properties
USF_InteractableComponent::USF_InteractableComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USF_InteractableComponent::SetInRange(bool isInRange)
{
	InRange = isInRange;
	OnStatusChanged.Broadcast();
}

void USF_InteractableComponent::SetIsActive(bool isActive)
{
	Active = isActive;
	OnStatusChanged.Broadcast();
}

void USF_InteractableComponent::RegisterInteractable()
{
	if (const auto CharacterRef = Cast<ASF_Character_Main>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		CharacterRef->GetInteractionSystem()->RegisterInteractable(this);
	}
}

void USF_InteractableComponent::UnRegisterInteractable()
{
	if (const auto CharacterRef = Cast<ASF_Character_Main>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		CharacterRef->GetInteractionSystem()->UnRegisterInteractable(this);
	}
}


// Called when the game starts
void USF_InteractableComponent::BeginPlay()
{

	Super::BeginPlay();
	RegisterInteractable();

	// Spawn Widget Component
	if (!InteractWidgetComponent)
	{
		const FName InteractWidgetName = FName(this->GetReadableName().Append("_Widget"));
		InteractWidgetComponent = NewObject<USF_InteractionWidgetComponent>(this, USF_InteractionWidgetComponent::StaticClass(), InteractWidgetName);

		InteractWidgetComponent->SetupAttachment(this);
		InteractWidgetComponent->RegisterComponent();
		InteractWidgetComponent->SetWorldLocation(GetComponentLocation());

		InteractWidgetComponent->InteractableComponent = this;
		InteractWidgetComponent->BindStatusChange();
	}
}

void USF_InteractableComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UnRegisterInteractable();

	if (InteractWidgetComponent)
	{
		InteractWidgetComponent->DestroyComponent();
	}
}
