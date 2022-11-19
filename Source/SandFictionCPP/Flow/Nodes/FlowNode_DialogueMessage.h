// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Nodes/FlowNode.h"
#include "FlowNode_DialogueMessage.generated.h"
/**
 * 
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Dialogue Message"))
class SANDFICTIONCPP_API UFlowNode_DialogueMessage final : public UFlowNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		FDataTableRowHandle NPCData;

	UPROPERTY(EditAnywhere)
		TArray<FText> DialogueLines;

	FText GetReadableDialogueString() const;
	FText GetSpeakerName() const;
	FLinearColor GetSpeakerColor() const;

	void TriggerOutput(const bool Finish);

	virtual void ExecuteInput(const FName& PinName) override;
};
