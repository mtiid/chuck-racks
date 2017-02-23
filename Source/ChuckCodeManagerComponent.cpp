/*
  ==============================================================================

    ChuckCodeManagerComponent.cpp
    Created: 14 Feb 2017 10:54:47pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ChuckCodeManagerComponent.h"

//==============================================================================
ChuckCodeManagerComponent::ChuckCodeManagerComponent(ChuckCodeModelManager* modelManager)    :
    tabView(TabbedButtonBar::Orientation::TabsAtTop)
{
    mModelManager = modelManager;
    addAndMakeVisible(tabView);
    
    for (auto& fc : mModelManager->chuckCodeModelCollection)
        addNewChuckCodeComponent(fc.second);

}

ChuckCodeManagerComponent::~ChuckCodeManagerComponent()
{
}

void ChuckCodeManagerComponent::paint (Graphics& g)
{
}

void ChuckCodeManagerComponent::resized()
{
    tabView.setBounds(0, 0, getWidth(), getHeight());
}


void ChuckCodeManagerComponent::addNewChuckCodeComponent(ChuckCodeModel* chuckCodeModel){
    ChuckCodeComponent* newChuckCodeComponent = new ChuckCodeComponent(chuckCodeModel);
    chuckCodeComponents.add(newChuckCodeComponent);
    tabView.addTab("New", Colour(100, 106, 127), newChuckCodeComponent, false);
}



