// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SandFictionCPP/Flow/Nodes/FlowNode_DialogueMessage.h"
#include "SF_HUD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogueLinesFinished, bool, bFinish);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerReplyGiven, int32, Index);

UCLASS()
class SANDFICTIONCPP_API ASF_HUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FDialogueLineStruct> DialogueLineArray;

	UPROPERTY(BlueprintReadWrite)
	FText DialogueSpeaker;

	UPROPERTY(BlueprintReadWrite)
	TArray<FText> PlayerReplyArray;

	void SetDialogueLines(TArray<FDialogueLineStruct> DialogueLines);
	void SetPlayerReplies(TArray<FText> PlayerReplies);
	void SetDialogueSpeaker(const FText SpeakerName);

	// Main Dialogue Functions

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StartMainDialogue();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateMainDialogue();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void EndMainDialogue();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowPlayerReplies();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void RemovePlayerReplies();

	// Side Dialogue Functions

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SpawnSideDialogue();

	

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FDialogueLinesFinished OnAllDialogueLinesFinished;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FPlayerReplyGiven OnPlayerAnswered;
	
};
