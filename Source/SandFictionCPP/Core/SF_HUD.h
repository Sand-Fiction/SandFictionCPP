// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SF_HUD.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDialogueLinesFinished, bool, bFinish);

UCLASS()
class SANDFICTIONCPP_API ASF_HUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		TArray<FText> DialogueLineArray;

	UPROPERTY(BlueprintReadWrite)
		FText DialogueSpeaker;

	UPROPERTY(BlueprintReadWrite)
		TArray<FText> PlayerReplyArray;

	void SetDialogueLines(TArray<FText> DialogueLines);
	void SetPlayerReplies(TArray<FText> PlayerReplies);
	void SetDialogueSpeaker(const FText SpeakerName);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ShowPlayerReplies();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateMainDialogue();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void StartMainDialogue();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SpawnSideDialogue();

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FDialogueLinesFinished OnAllDialogueLinesFinished;
	
};
