// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowGraphNode_DialogueMessage.h"
#include "Graph/Widgets/SFlowGraphNode.h"
#include "SandFictionCPP/Flow/Nodes/FlowNode_DialogueMessage.h"
#include "SandFictionCPP_Editor/Flow/Widgets/SFlowGraphNode_DialogueMessage.h"

UFlowGraphNode_DialogueMessage::UFlowGraphNode_DialogueMessage(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AssignedNodeClasses = { UFlowNode_DialogueMessage::StaticClass() };
}

TSharedPtr<SGraphNode> UFlowGraphNode_DialogueMessage::CreateVisualWidget()
{
	return SNew(SFlowGraphNode_DialogueMessage, this);
}