// Fill out your copyright notice in the Description page of Project Settings.

#include "SF_Character_Enemy.h"
#include "FlowSubsystem.h"
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

	TargetComponent->DestroyComponent();
}
