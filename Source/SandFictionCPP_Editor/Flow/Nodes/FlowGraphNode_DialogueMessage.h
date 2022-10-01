// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Graph/Nodes/FlowGraphNode.h"
#include "UObject/Object.h"
#include "FlowGraphNode_DialogueMessage.generated.h"

/**
 * 
 */
UCLASS()
class SANDFICTIONCPP_EDITOR_API UFlowGraphNode_DialogueMessage : public UFlowGraphNode
{
	GENERATED_UCLASS_BODY()

	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	
};
