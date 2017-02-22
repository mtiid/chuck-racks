/*
  ==============================================================================

    CodeDocumentManagerComponent.cpp
    Created: 14 Feb 2017 10:54:47pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "CodeDocumentManagerComponent.h"

//==============================================================================
CodeDocumentManagerComponent::CodeDocumentManagerComponent(FileContainerManagerModel* managerModel)    :
    tabView(TabbedButtonBar::Orientation::TabsAtTop)
{
    mManagerModel = managerModel;
    
    addAndMakeVisible(tabView);
    
    for (auto& fc : mManagerModel->fileContainerModelCollection)
        addNewFileContainerUI(fc.second);

}

CodeDocumentManagerComponent::~CodeDocumentManagerComponent()
{
}

void CodeDocumentManagerComponent::paint (Graphics& g)
{
}

void CodeDocumentManagerComponent::resized()
{
    tabView.setBounds(0, 0, getWidth(), getHeight());
}


void CodeDocumentManagerComponent::addNewFileContainerUI(FileContainerModel* fileContainerModel){
    FileContainerUI* newFileContainerUI = new FileContainerUI(fileContainerModel);
    fileContainerUIs.add(newFileContainerUI);
    tabView.addTab("New", Colour(100, 106, 127), newFileContainerUI, false);
}



