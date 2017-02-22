//
//  MainViewComponent.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 10/22/15.
//
//

#include "MainViewComponent.h"

MainViewComponent::MainViewComponent(ChuckRacksAudioProcessor* processor_) :
    processor(processor_),
    verticalDividerBar (&verticalLayout, 1, true),
    editorArea(processor->getChuckCodeModelManager()),
    parameterUI(processor_)

{
    verticalLayout.setItemLayout (0, 5, getParentWidth()-5,
                                        getParentWidth()-5);    // editor area
    verticalLayout.setItemLayout (1, 5, 5, 5);                  // divider bar
    verticalLayout.setItemLayout (2, -0.4, -0.6, -0.4);               // parameter area

    addChildComponent(parameterUI);
    addAndMakeVisible(verticalDividerBar);
    addAndMakeVisible(editorArea);
    
}

MainViewComponent::~MainViewComponent()
{
    
}

void MainViewComponent::paint(Graphics& g)
{
}

void MainViewComponent::resized()
{
    refresh(parameterUI.isVisible());
}

void MainViewComponent::toggleParamListVisibility()
{
    // Toggle the visibility of the Parameter List UI and refresh the UI
    parameterUI.setVisible(!parameterUI.isVisible());
    refresh(parameterUI.isVisible());
}

void MainViewComponent::addNewChuckCodeComponent(ChuckCodeModel* chuckCodeModel){
    editorArea.addNewChuckCodeComponent(chuckCodeModel);
}


void MainViewComponent::refresh(bool paramListVisible)
{
    Rectangle<int> r (getLocalBounds());
    
    Array<Component*> vcomps;
    
    if (paramListVisible) {
        vcomps.clear();
        vcomps.add(&editorArea);
        vcomps.add(&verticalDividerBar);
        vcomps.add(&parameterUI);
    }else{
        vcomps.clear();
        vcomps.add(&editorArea);
    }
    
    verticalLayout.layOutComponents (vcomps.getRawDataPointer(), vcomps.size(),
                                     r.getX(), r.getY(), r.getWidth(), r.getHeight(),
                                     false,     // lay out side-by-side
                                     true);     // resize the components' heights as well as widths
}
