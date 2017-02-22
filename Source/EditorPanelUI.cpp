/*
  ==============================================================================

    EditorPanelUI.cpp
    Created: 14 Feb 2017 9:28:38pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "EditorPanelUI.h"

//==============================================================================
EditorPanelUI::EditorPanelUI(ChuckCodeModelManager* modelManager):
    codeManagerComponent(modelManager),
    horizontalDividerBar (&horizontalLayout, 1, false)
{
    consoleComponent = new ConsoleComponent();
    addAndMakeVisible(codeManagerComponent);
    addAndMakeVisible(consoleComponent);
    addAndMakeVisible(horizontalDividerBar);

    // set up layout manager limits
    horizontalLayout.setItemLayout (0, -0.1, -1.0, -0.9);   // code area
    horizontalLayout.setItemLayout (1, 5, 5, 5);            // divider bar
    horizontalLayout.setItemLayout (2, -0.1, -0.5, -0.1);      // console area

}

EditorPanelUI::~EditorPanelUI()
{
}

void EditorPanelUI::paint (Graphics& g)
{
    
}

void EditorPanelUI::resized()
{
    Rectangle<int> r (getLocalBounds().reduced (0));
    
    // make a list of two of our child components that we want to reposition
    Component* comps[] = { &codeManagerComponent, &horizontalDividerBar, consoleComponent.get() };
    
    // this will position the 3 components, one above the other, to fit
    // vertically into the rectangle provided.
    horizontalLayout.layOutComponents (comps, 3,
                                       r.getX(), r.getY(), r.getWidth(), r.getHeight(),
                                       true, true);
}

void EditorPanelUI::addNewChuckCodeComponent(ChuckCodeModel* chuckCodeModel){
    codeManagerComponent.addNewChuckCodeComponent(chuckCodeModel);
    chuckCodeModel->addListener(consoleComponent);
}

