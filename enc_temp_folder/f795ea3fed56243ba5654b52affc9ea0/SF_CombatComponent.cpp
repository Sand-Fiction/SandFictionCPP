// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_CombatComponent.h"

// Sets default values for this component's properties
USF_CombatComponent::USF_CombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void USF_CombatComponent::MeleeAttack()
{
	if (const auto OwningCharacter = Cast<ASF_Character>(GetOwner()))
	{
		if (AnimDataTable != nullptr)
		{
			const auto AnimData = AnimDataTable->FindRow<FCharacterAnimationData>(TEXT("MeleeAttack01"), TEXT("MeleeAttack01 not found in AnimDT."), true);
			if (AnimData->AnimMontage)
			{
				OwningCharacter->PlayAnimMontage(AnimData->AnimMontage);
			}
		}
	}
}

void USF_CombatComponent::GetHit(USF_CombatComponent* Source)
{

}

// Called when the game starts
void USF_CombatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);

	// ...
	
}


// Called every frame
void USF_CombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// .ToDo: Regen Health here...
}

