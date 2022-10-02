// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowNode_DialogueMessage.h"

#include "Kismet/GameplayStatics.h"
#include "SandFictionCPP/Core/SF_HUD.h"
#include "SandFictionCPP/Data/NPCData.h"


FText UFlowNode_DialogueMessage::GetReadableDialogueString() const
{
	FText DialogueText;

	for (const FText DialogueLine :DialogueLines)
	{
		FFormatNamedArguments Args;
		Args.Add("OldLines", DialogueText);
		Args.Add("NewLine", DialogueLine);

		DialogueText = FText::Format(NSLOCTEXT("SFNameSpace", "FullTextFormat", "{OldLines} {NewLine}"), Args);
	}

	return DialogueText;
}

FText UFlowNode_DialogueMessage::GetSpeakerName() const
{
	if (NPCData.DataTable)
	{
		if (NPCData.RowName != FName(TEXT("none")))
		{
			const FNPCData* NPCStruct = NPCData.DataTable->FindRow<FNPCData>(NPCData.RowName, "");
			return NPCStruct->Name;
		}
		return FText::FromString("Missing Row!");
	}
	return FText::FromString("Missing Data Table!");
}

FLinearColor UFlowNode_DialogueMessage::GetSpeakerColor() const
{
	if (NPCData.DataTable)
	{
		if (NPCData.RowName != FName(TEXT("None")))
		{
			const FNPCData* NPCStruct = NPCData.DataTable->FindRow<FNPCData>(NPCData.RowName, "");
			return NPCStruct->NodeColor;
		}
	}
	return FLinearColor::White;
}

void UFlowNode_DialogueMessage::ExecuteInput(const FName& PinName)
{
	if (const auto HUD = Cast<ASF_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
	{
		HUD->SetDialogueLines(DialogueLines);
		HUD->SetDialogueSpeaker(GetSpeakerName());
		HUD->UpdateMainDialogue();
		HUD->OnAllDialogueLinesFinished.AddDynamic(this, &UFlowNode_DialogueMessage::TriggerFirstOutput);
	}
}