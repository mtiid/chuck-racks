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
    for (int i=0; i<fileContainerUIs.size(); i++) {
        fileContainerUIs[i]->removeChangeListener(this);
    }
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
    
    for(int i=0; i<m_managerModel->fileContainerModels.size(); i++)
    {
        FileContainerUI* newFileContainerUI = new FileContainerUI(m_managerModel->fileContainerModels[i]);
        newFileContainerUI->addChangeListener(this);
        fileContainerUIs.add(newFileContainerUI);
        mainView.addAndMakeVisible(newFileContainerUI);
        if (i==0) {
            newFileContainerUI->setTopLeftPosition(0, 0);
        }else{
            newFileContainerUI->setTopLeftPosition(0, fileContainerUIs[i-1]->getBottom());
        }
        
        newFileContainerUI->init();
    }

    mainView.setBounds(0, 0, getWidth()-18, (getHeight()-200)*fileContainerUIs.size());
    
    /*
    //-------
    FileContainerUI* newFileContainerUI = new FileContainerUI(m_managerModel->fileContainerModels[m_managerModel->fileContainerModels.size()-1]);
    newFileContainerUI->init();

    newFileContainerUI->addChangeListener(this);
    fileContainerUIs.add(newFileContainerUI);
    mainView.addAndMakeVisible(newFileContainerUI);
    //if (fileContainerUIs.size()==1) {
    //    newFileContainerUI->setTopLeftPosition(0, 0);
    //}else{
    //    newFileContainerUI->setTopLeftPosition(0, fileContainerUIs[fileContainerUIs.size()-2]->getBottom());
    //}
    
    //}
    mainView.setBounds(0, 0, getWidth(), fileContainerUIs.getLast()->getBottom());
    */
}

void FileContainerManagerUI::changeListenerCallback(ChangeBroadcaster *source){
    
    // Attempt to cast the changebroadcaster as a FileContainerUI
    FileContainerUI* fileContainerUI = dynamic_cast<FileContainerUI*>(source);
    
    // If successful, update our layout
    if (fileContainerUI != nullptr ) {
        updateFileContainerUILayout();
    }
}

void FileContainerManagerUI::updateFileContainerUILayout(){
    
    // Update the vertical position of each of the file containers
    for(int i=0; i<fileContainerUIs.size(); i++)
    {
        FileContainerUI* currentFileContainerUI = fileContainerUIs[i];
        if (i==0) {
            currentFileContainerUI->setTopLeftPosition(0, 0);
        }else{
            currentFileContainerUI->setTopLeftPosition(0, fileContainerUIs[i-1]->getBottom());
        }
    }
    
    mainView.setBounds(0, 0, getWidth(), fileContainerUIs.getLast()->getBottom());

}

