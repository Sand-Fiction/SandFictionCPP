// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_CharacterStateComponent.h"

// Sets default values for this component's properties
USF_CharacterStateComponent::USF_CharacterStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void USF_CharacterStateComponent::ChangeCharacterState(ECharacterState NewCharacterState)
{
	const ECharacterState OldCharacterState = CharacterState;
	CharacterState = NewCharacterState;
	OnCharacterStateChanged.Broadcast(OldCharacterState, NewCharacterState);
}

// Called when the game starts
void USF_CharacterStateComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USF_CharacterStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

