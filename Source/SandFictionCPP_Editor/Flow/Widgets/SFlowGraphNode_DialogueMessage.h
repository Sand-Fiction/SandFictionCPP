#pragma once

#include "CoreMinimal.h"
#include "Graph/Widgets/SFlowGraphNode.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class SANDFICTIONCPP_EDITOR_API SFlowGraphNode_DialogueMessage : public SFlowGraphNode
{
protected:
	
	virtual void UpdateGraphNode() override;

	virtual TSharedRef<SWidget> CreateDialogueContentArea();
	virtual TSharedRef<SWidget> CreateNodeContentArea() override;
	virtual void CreateBelowPinControls(TSharedPtr<SVerticalBox> MainBox) override;
	
	virtual TSharedRef<SWidget> CreateTitleBar();



public:

	/** Used to display the name of the node and allow renaming of the node */
	TSharedPtr<SVerticalBox> TitleBox;
	TSharedPtr<SHorizontalBox> TitleBoxH;
	
	FSlateBrush Brush;
	FSlateColor SpeakerTextColor;
	FSlateBrush SpeakerBgBrush;
};