// Fill out your copyright notice in the Description page of Project Settings.

#include "SF_HUD.h"

#include "SF_GameInstance.h"
#include "Kismet/GameplayStatics.h"

ASF_HUD::ASF_HUD()
{
	LoadingScreenFadeTime = 2.0f;
}

void ASF_HUD::SetDialogueLines(TArray<FDialogueLineStruct> DialogueLines)
{
	DialogueLineArray = DialogueLines;
}

void ASF_HUD::SetPlayerReplies(TArray<FText> PlayerReplies)
{
	PlayerReplyArray = PlayerReplies;
}

void ASF_HUD::SetDialogueSpeaker(const FText SpeakerName)
{
	DialogueSpeaker = SpeakerName;
}

float ASF_HUD::HideLoadingScreen_Implementation()
{
	if (!GetWorld())
	{
		return -1;
	}

	if (const auto GameInstance = Cast<USF_GameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		if (!GameInstance->LoadingScreenWidget)
		{
			return -1;
		}
	}

	return LoadingScreenFadeTime;
}

float ASF_HUD::ShowLoadingScreen_Implementation()
{
	if (!GetWorld())
	{
		return -1;
	}

	if (const auto GameInstance = Cast<USF_GameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		if (GameInstance->LoadingScreenWidget)
		{
			return -1;
		}
	}

	return LoadingScreenFadeTime;
}
