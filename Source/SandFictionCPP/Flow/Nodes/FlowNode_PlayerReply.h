// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "FlowNode_PlayerReply.generated.h"

UCLASS(NotBlueprintable, meta = (DisplayName = "Player Reply"))
class SANDFICTIONCPP_API UFlowNode_PlayerReply final : public UFlowNode
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere)
		TArray<FText> PlayerReplies;

	TArray<FText> GetReadablePlayerReplyString() const;
	FText GetSpeakerName() const;
	static FLinearColor GetSpeakerColor();

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	void UpdateReplyPins();
	
	virtual void ExecuteInput(const FName& PinName) override;

	UFUNCTION()
	void TriggerOutPutAtIndex(int32 Index);
	
};
