// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowNode_DialogueMessage.h"
#include "SandFictionCPP/Data/NPCData.h"


FText UFlowNode_DialogueMessage::GetReadableDialogueString() const
{
	FText DialogueText;

	for (const FText DialogueLine :DialogueLines)
	{
		FFormatNamedArguments Args;
		Args.Add("OldLines", DialogueText);
		Args.Add("NewLine", DialogueLine);

		DialogueText = FText::Format(NSLOCTEXT("SFNameSpace", "FullTextFormat", "{OldLines} \n {NewLine}"), Args);
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
	// Node Functionality here!

	TriggerFirstOutput(true);
}
