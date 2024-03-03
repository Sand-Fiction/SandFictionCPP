// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Nodes/Utils/FlowNode_Checkpoint.h"
#include "FlowGraphNode_Checkpoint.generated.h"

/**
 * Save the state of the game to the save file.
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Sand Fiction Checkpoint", Keywords = "autosave, save"))
class SANDFICTIONCPP_EDITOR_API UFlowGraphNode_Checkpoint : public UFlowNode
{
	GENERATED_UCLASS_BODY()

	virtual void ExecuteInput(const FName& PinName) override;
	virtual void OnLoad_Implementation() override;
};
