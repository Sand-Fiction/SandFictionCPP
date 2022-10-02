// Fill out your copyright notice in the Description page of Project Settings.


#include "SF_HUD.h"

void ASF_HUD::SetDialogueLines(TArray<FText> DialogueLines)
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
