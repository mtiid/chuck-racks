/*
  ==============================================================================

    EditorPanelUI.h
    Created: 14 Feb 2017 9:28:38pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#ifndef EDITORPANELUI_H_INCLUDED
#define EDITORPANELUI_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ChuckCodeManagerComponent.h"
#include "CRTabbedComponent.h"
#include "ChuckCodeModelManager.h"
#include "ConsoleComponent.h"

//==============================================================================
/*
*/
class EditorPanelUI    : public Component
{
public:
    EditorPanelUI(ChuckCodeModelManager* modelManager);
    ~EditorPanelUI();

    void paint (Graphics&) override;
    void resized() override;
    void addNewChuckCodeComponent(ChuckCodeModel* chuckCodeModel);

private:
    
    ChuckCodeManagerComponent codeManagerComponent;
    ScopedPointer<TextEditor> consoleComponent;
    //ScopedPointer<ConsoleComponent> consoleComponent;
    
    StretchableLayoutManager horizontalLayout;
    StretchableLayoutResizerBar horizontalDividerBar;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditorPanelUI)
};


#endif  // EDITORPANELUI_H_INCLUDED
