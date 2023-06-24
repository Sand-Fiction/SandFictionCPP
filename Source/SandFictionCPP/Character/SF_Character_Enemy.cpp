// Fill out your copyright notice in the Description page of Project Settings.

#include "SF_Character_Enemy.h"
#include "FlowSubsystem.h"
#include "NavigationSystem.h"
#include "SandFictionCPP/Actors/Items/SF_ItemActor.h"
#include "SandFictionCPP/Components/SF_CharacterFactionComponent.h"
#include "SandFictionCPP/Components/SF_CharacterTargetComponent.h"

ASF_Character_Enemy::ASF_Character_Enemy()
{
	GetFactionComponent()->SetFaction(ECharacterFaction::Enemy);
	FlowComponent = CreateDefaultSubobject<UFlowComponent>(TEXT("FlowComponent"));
	TargetComponent = CreateDefaultSubobject<USF_CharacterTargetComponent>(TEXT("TargetComponent"));
	TargetComponent->SetupAttachment(GetRootComponent());
}

void ASF_Character_Enemy::StartDeath()
{
	Super::StartDeath();

	SpawnItemDrop();

	TargetComponent->DestroyComponent();
}

void ASF_Character_Enemy::SpawnItemDrop() const
{
	if (GetWorld() && ItemDropClass)
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation;
		SpawnRotation.Yaw = FMath::FRandRange(-180.f, 180.f);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		if (UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld()))
		{
			FNavLocation ResultLocation;
			if (NavSystem->GetRandomPointInNavigableRadius(GetActorLocation(), 50.f, ResultLocation))
			{
				FHitResult OutHit;
				SpawnLocation = ResultLocation;
				if (GetWorld()->LineTraceSingleByChannel(OutHit, SpawnLocation, SpawnLocation - FVector(0.f, 0.f, 100.f), ECC_Visibility))
				{
					SpawnLocation = OutHit.Location;
				}
			}
		}

		GetWorld()->SpawnActor<ASF_ItemActor>(ItemDropClass, SpawnLocation, SpawnRotation, SpawnParameters);
	}
}
