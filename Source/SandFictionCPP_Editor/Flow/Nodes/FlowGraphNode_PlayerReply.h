// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Graph/Nodes/FlowGraphNode.h"
#include "FlowGraphNode_PlayerReply.generated.h"

/**
 * 
 */
UCLASS()
class SANDFICTIONCPP_EDITOR_API UFlowGraphNode_PlayerReply : public UFlowGraphNode
{
	GENERATED_UCLASS_BODY()

	virtual TSharedPtr<SGraphNode> CreateVisualWidget() override;
	
};
