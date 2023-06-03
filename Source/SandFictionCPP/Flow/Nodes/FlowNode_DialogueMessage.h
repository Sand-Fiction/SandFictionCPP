// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Nodes/FlowNode.h"
#include "FlowNode_DialogueMessage.generated.h"

USTRUCT(BlueprintType)
struct FDialogueLineStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText DialogueLine;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UAnimMontage* AnimMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USoundBase* Voice;

	FDialogueLineStruct()
	{
		DialogueLine = FText();
		AnimMontage = nullptr;
		Voice = nullptr;
	}

	FDialogueLineStruct(const FText Dialogue)
	{
		DialogueLine = Dialogue;
		AnimMontage = nullptr;
		Voice = nullptr;
	}
};

UCLASS(NotBlueprintable, meta = (DisplayName = "Dialogue Message"))
class SANDFICTIONCPP_API UFlowNode_DialogueMessage final : public UFlowNode
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle NPCData;

	UPROPERTY(EditAnywhere)
	TArray<FText> DialogueLines;

	UPROPERTY(EditAnywhere)
	TArray<FDialogueLineStruct> NewDialogueLines;

	UFUNCTION(CallInEditor)
	void DEBUG_FillInStructs();

	FText GetReadableDialogueString() const;
	FText GetSpeakerName() const;
	FLinearColor GetSpeakerColor() const;

	UFUNCTION()
	void UnbindAndTriggerOutput(const bool Finish);

	virtual void ExecuteInput(const FName& PinName) override;
};
