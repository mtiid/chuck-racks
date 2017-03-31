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
    tabView.addTab("New", Colour(100, 106, 127), newChuckCodeComponent, false);
}

void ChuckCodeManagerComponent::removeChuckCodeComponent(int tabIndex){
    //for (int i=0; i<mModelManager->chuckCodeModelCollection.size(); ++i){
    //    if (i == tabIndex){
    //        DBG("removing");
    //        mModelManager->removeFileContainer(mModelManager->chuckCodeModelCollection.at(i));
    auto it = mModelManager->chuckCodeModelCollection.begin();
    std::advance(it, tabIndex);
    mModelManager->removeFileContainer(it->second);
    chuckCodeComponents.remove(tabIndex);
    //    }
    //}
}

void ChuckCodeManagerComponent::removeTabComponent(int tabIndex){
    removeChuckCodeComponent(tabIndex);
}



