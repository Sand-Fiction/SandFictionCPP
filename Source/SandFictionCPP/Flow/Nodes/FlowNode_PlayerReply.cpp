// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowNode_PlayerReply.h"

#include "Kismet/GameplayStatics.h"
#include "SandFictionCPP/Core/SF_HUD.h"

UFlowNode_PlayerReply::UFlowNode_PlayerReply(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UpdateReplyPins();
}

TArray<FText> UFlowNode_PlayerReply::GetReadablePlayerReplyString() const
{
	return PlayerReplies;
}

FText UFlowNode_PlayerReply::GetSpeakerName() const
{
	return FText::FromString("Player");
}

FLinearColor UFlowNode_PlayerReply::GetSpeakerColor()
{
	return FLinearColor::White;
}

#if WITH_EDITOR
void UFlowNode_PlayerReply::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	UpdateReplyPins();
}
#endif

void UFlowNode_PlayerReply::UpdateReplyPins()
{
	OutputPins.Empty();
	if (PlayerReplies.Num() > 0)
	{
		for (const FText& PlayerReply : PlayerReplies)
		{
			OutputPins.Add(FFlowPin(PlayerReply));
		}
	}
}

void UFlowNode_PlayerReply::ExecuteInput(const FName& PinName)
{
	if (const auto HUD = Cast<ASF_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
	{
		HUD->SetPlayerReplies(PlayerReplies);
		HUD->ShowPlayerReplies();

		if (!HUD->OnPlayerAnswered.IsAlreadyBound(this, &UFlowNode_PlayerReply::TriggerOutPutAtIndex))
		{
			HUD->OnPlayerAnswered.AddDynamic(this, &UFlowNode_PlayerReply::TriggerOutPutAtIndex);
		}
	}
}

void UFlowNode_PlayerReply::TriggerOutPutAtIndex(const int32 Index)
{
	if (OutputPins.Num() > 0)
	{
		if (OutputPins[Index].IsValid())
		{
			const FFlowPin OutputPin = OutputPins[Index];
	
			TriggerOutput(OutputPin.PinName);

			if (const auto HUD = Cast<ASF_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
			{
				HUD->OnPlayerAnswered.RemoveDynamic(this, &UFlowNode_PlayerReply::TriggerOutPutAtIndex);
			}
		}
	}
}
