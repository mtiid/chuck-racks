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
#include "CodeDocumentManagerComponent.h"
#include "ConsoleComponent.h"

//==============================================================================
/*
*/
class EditorPanelUI    : public Component
{
public:
    EditorPanelUI(FileContainerManagerModel* managerModel);
    ~EditorPanelUI();

    void paint (Graphics&) override;
    void resized() override;
    void addNewFileContainerUI(FileContainerModel* fileContainerModel);

private:
    
    CodeDocumentManagerComponent codeManagerComponent;
    ConsoleComponent consoleComponent;
    
    StretchableLayoutManager horizontalLayout;
    StretchableLayoutResizerBar horizontalDividerBar;

    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EditorPanelUI)
};


#endif  // EDITORPANELUI_H_INCLUDED
