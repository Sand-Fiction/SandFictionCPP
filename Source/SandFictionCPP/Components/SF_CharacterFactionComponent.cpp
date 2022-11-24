// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_CharacterFactionComponent.h"

// Sets default values for this component's properties
USF_CharacterFactionComponent::USF_CharacterFactionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USF_CharacterFactionComponent::SetFaction(ECharacterFaction NewFaction)
{
	Faction = NewFaction;
}

bool USF_CharacterFactionComponent::IsHostile(USF_CharacterFactionComponent* OtherFactionComponent)
{
	if(OtherFactionComponent)
	{
		switch (Faction)
		{
			// If Faction is Player, look for Enemy
		case ECharacterFaction::Player:
		{
			if (OtherFactionComponent->Faction == ECharacterFaction::Enemy)
			{
				return true;
			}
		}

		// Neutral is never hostile
		case ECharacterFaction::Neutral: return false;

			// If Faction is Enemy, look for Player
		case ECharacterFaction::Enemy:
		{
			{
				if (OtherFactionComponent->Faction == ECharacterFaction::Player)
				{
					return true;
				}
			}
		}

		default: return false;
		}
	}
	else
	{
		return false;
	}
}


// Called when the game starts
void USF_CharacterFactionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USF_CharacterFactionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

