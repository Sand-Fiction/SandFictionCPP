// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_Character_NPC.h"

#include "FlowAsset.h"
#include "FlowSubsystem.h"
#include "SandFictionCPP/Components/SF_CharacterFactionComponent.h"
#include "SandFictionCPP/Components/SF_InteractableComponent.h"

ASF_Character_NPC::ASF_Character_NPC()
{
	GetFactionComponent()->SetFaction(ECharacterFaction::Friendly);
	InteractableComponent = CreateDefaultSubobject<USF_InteractableComponent>(TEXT("InteractableComponent"));
	InteractableComponent->SetupAttachment(GetRootComponent());

	FlowComponent = CreateDefaultSubobject<UFlowComponent>(TEXT("FlowComponent"));
}

void ASF_Character_NPC::BeginPlay()
{
	Super::BeginPlay();

	GetInteractableComponent()->OnInteraction.AddDynamic(this, &ASF_Character_NPC::StartDialogue);
}

void ASF_Character_NPC::StartDialogue()
{
	FlowComponent->NotifyGraph(Dialogue);
}
