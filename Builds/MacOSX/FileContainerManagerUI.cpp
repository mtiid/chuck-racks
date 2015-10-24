//
//  FileContainerManagerUI.cpp
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "FileContainerManagerUI.h"


FileContainerManagerUI::FileContainerManagerUI(FileContainerManagerModel* managerModel)
{
    m_managerModel=managerModel;
}


FileContainerManagerUI::~FileContainerManagerUI(){
    
}


void FileContainerManagerUI::paint(Graphics& g){
    
    g.fillAll(Colours::lightgrey);
    g.setColour(Colours::darkgrey);
    g.drawRect(getLocalBounds(), 1);
    g.setColour(Colours::darkgrey);
    g.drawFittedText("Please add a ChucK Editor", getWidth() * 0.5, getHeight() * 0.5, 100, 50, juce::Justification::centred, 2);
    
}

void FileContainerManagerUI::init(){
    scrollableView.setBounds(getLocalBounds());
    mainView.setBounds(0, 0, getWidth(), getHeight());
    addAndMakeVisible(&scrollableView);
    scrollableView.setViewedComponent(&mainView);

    addNewFileContainerUI();
}

void FileContainerManagerUI::addNewFileContainerUI(){
    fileContainerUIs.clear();
    
    for(int i=0; i< m_managerModel->fileContainerModels.size(); i++)
    {
        //fileContainerUIs.pop_back();
        FileContainerUI* newFileContainerUI = new FileContainerUI(m_managerModel->fileContainerModels[i]);
        fileContainerUIs.add(newFileContainerUI);
        mainView.addAndMakeVisible(newFileContainerUI);
        newFileContainerUI->setBounds(0, (getHeight()-200)*i, getWidth()-18, getHeight()-200);
        newFileContainerUI->init();
    }
    
    mainView.setBounds(0, 0, getWidth()-18, (getHeight()-200)*fileContainerUIs.size());
    /*if(scrollableView.isVerticalScrollBarShown()){
        mainView.setBounds(0, 0, getWidth()-18, (getHeight()-200)*fileContainerUIs.size());
    }*/
}

