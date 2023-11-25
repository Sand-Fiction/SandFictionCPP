// Fill out your copyright notice in the Description page of Project Settings.

#include "SF_GameMode_Gameplay.h"

#include "FlowComponent.h"
#include "FlowWorldSettings.h"
#include "Kismet/GameplayStatics.h"
#include "SandFictionCPP/Core/SF_GameInstance.h"
#include "SandFictionCPP/Core/Subsystems/NPCManager/SF_NPCManager.h"

void ASF_GameMode_Gameplay::BeginPlay()
{
	Super::BeginPlay();
}

void ASF_GameMode_Gameplay::SpawnAllNPCs()
{
	if (const auto NPCManager = UGameplayStatics::GetGameInstance(this)->GetSubsystem<USF_NPCManager>())
	{
		if (const auto FlowWorldSettings = Cast<AFlowWorldSettings>(GetWorld()->GetWorldSettings()))
		{
			NPCManager->SpawnAllNPCsInWorld(FlowWorldSettings->GetFlowComponent()->IdentityTags.First());
		}
	}
}
