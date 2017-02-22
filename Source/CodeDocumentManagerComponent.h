/*
  ==============================================================================

    CodeDocumentManagerComponent.h
    Created: 14 Feb 2017 10:54:47pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#ifndef CODEDOCUMENTMANAGERCOMPONENT_H_INCLUDED
#define CODEDOCUMENTMANAGERCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "FileContainerManagerModel.h"


//==============================================================================
/*
*/
class CodeDocumentManagerComponent    : public Component
{
    
public:
    CodeDocumentManagerComponent(FileContainerManagerModel* managerModel);
    ~CodeDocumentManagerComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void addNewFileContainerUI(FileContainerModel* fileContainerModel);


private:
    FileContainerManagerModel* mManagerModel;
    OwnedArray<FileContainerUI> fileContainerUIs;

    TabbedComponent tabView;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CodeDocumentManagerComponent)
};


#endif  // CODEDOCUMENTMANAGERCOMPONENT_H_INCLUDED
