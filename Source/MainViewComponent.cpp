//
//  MainViewComponent.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 10/22/15.
//
//

#include "MainViewComponent.h"

MainViewComponent::MainViewComponent()
{
    
}

MainViewComponent::~MainViewComponent()
{
    
}

void MainViewComponent::paint(Graphics& g)
{
    //g.fillAll(Colours::lightgrey);
    g.setColour(Colours::black);
    g.drawRect(getLocalBounds(), 1);
}

void MainViewComponent::resized()
{
    
}
