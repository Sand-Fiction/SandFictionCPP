// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_CharacterTargetComponent.h"
#include "SF_CharacterTargetSystem.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USF_CharacterTargetComponent::USF_CharacterTargetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void USF_CharacterTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	TargetSystem = UGameplayStatics::GetPlayerCharacter(this, 0)->FindComponentByClass<USF_CharacterTargetSystem>();

	TargetSystem->RegisterTargetComponent(this);
	
}

void USF_CharacterTargetComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	TargetSystem->UnRegisterTargetComponent(this);
}


