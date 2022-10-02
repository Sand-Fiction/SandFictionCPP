#pragma once

#include "CoreMinimal.h"
#include "Graph/Widgets/SFlowGraphNode.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */

class SANDFICTIONCPP_EDITOR_API SFlowGraphNode_PlayerReply : public SFlowGraphNode
{
protected:
	
	virtual void UpdateGraphNode() override;

	virtual TSharedRef<SWidget> CreateNodeContentArea() override;
	
	virtual TSharedRef<SWidget> CreateTitleBar();



public:
	SLATE_BEGIN_ARGS(SFlowGraphNode_PlayerReply) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UFlowGraphNode* InNode);


	/** Used to display the name of the node and allow renaming of the node */
	TSharedPtr<SVerticalBox> TitleBox;
	TSharedPtr<SHorizontalBox> TitleBoxH;
	
	FSlateBrush Brush;
	FSlateColor SpeakerTextColor;
	FSlateBrush SpeakerBgBrush;
};