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
ChuckCodeManagerComponent::ChuckCodeManagerComponent(ChuckCodeModelManager* modelManager)    //:
    //tabView(TabbedButtonBar::Orientation::TabsAtTop)
{
    mModelManager = modelManager;
    addAndMakeVisible(tabView);
    
    tabView.addListener(this);
    
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
    tabView.addTab("Untitled", Colour(100, 106, 127), newChuckCodeComponent, false);
}

void ChuckCodeManagerComponent::removeChuckCodeComponent(int tabIndex){
    auto it = mModelManager->chuckCodeModelCollection.begin();
    
    if (it != mModelManager->chuckCodeModelCollection.end())
    {
        if (tabIndex > 0)
            std::advance(it, tabIndex);
        
        tabView.removeTab(tabIndex);
        mModelManager->removeFileContainer(it->second);
    }
    
}

void ChuckCodeManagerComponent::removeTabComponent(int tabIndex){
    removeChuckCodeComponent(tabIndex);
}



