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

void UFlowNode_PlayerReply::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	UpdateReplyPins();
}

void UFlowNode_PlayerReply::UpdateReplyPins()
{
	OutputPins.Empty();

	for (const FText& PlayerReply : PlayerReplies)
	{
		OutputPins.Add(FFlowPin(PlayerReply));
	}
}

void UFlowNode_PlayerReply::ExecuteInput(const FName& PinName)
{
	if (const auto HUD = Cast<ASF_HUD>(UGameplayStatics::GetPlayerController(this, 0)->GetHUD()))
	{
		HUD->SetPlayerReplies(PlayerReplies);
		HUD->ShowPlayerReplies();
	}
}
