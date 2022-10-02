// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowGraphNode_PlayerReply.h"
#include "Graph/Widgets/SFlowGraphNode.h"
#include "SandFictionCPP/Flow/Nodes/FlowNode_PlayerReply.h"
#include "SandFictionCPP_Editor/Flow/Widgets/SFlowGraphNode_PlayerReply.h"

UFlowGraphNode_PlayerReply::UFlowGraphNode_PlayerReply(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AssignedNodeClasses = { UFlowNode_PlayerReply::StaticClass() };
}

TSharedPtr<SGraphNode> UFlowGraphNode_PlayerReply::CreateVisualWidget()
{
	return SNew(SFlowGraphNode_PlayerReply, this);
}
