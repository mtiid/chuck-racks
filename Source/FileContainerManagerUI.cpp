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
    mManagerModel=managerModel;
}


FileContainerManagerUI::~FileContainerManagerUI(){
    for (int i=0; i<fileContainerUIs.size(); i++) {
        fileContainerUIs[i]->removeChangeListener(this);
    }
}

void FileContainerManagerUI::paint(Graphics& g){
    g.fillAll(Colour(250, 250, 250));
    g.setColour(Colours::darkgrey);
    g.drawRect(getLocalBounds(), 1);
    g.setColour(Colours::darkgrey);
    g.drawFittedText("Please add a ChucK Editor", getWidth() * 0.5, getHeight() * 0.5, 100, 50, juce::Justification::centred, 2);
}

void FileContainerManagerUI::resized(){
    
}

void FileContainerManagerUI::init(){
    std::cout << "FileContainerManageUI::init" << std::endl;
    scrollableView.setBounds(getLocalBounds());
    mainView.setBounds(getLocalBounds());
    addAndMakeVisible(&scrollableView);
    scrollableView.setViewedComponent(&mainView);

    //addNewFileContainerUI();
    //std::cout << "model size: " << m_managerModel->fileContainerModels.size() << std::endl;
    for (int i=0; i<mManagerModel->fileContainerModels.size(); i++){
        addNewFileContainerUI(mManagerModel->fileContainerModels[i]);
    }
}

void FileContainerManagerUI::addNewFileContainerUI(FileContainerModel* fileContainerModel){
    FileContainerUI* newFileContainerUI = new FileContainerUI(fileContainerModel);
    fileContainerUIs.add(newFileContainerUI);

    newFileContainerUI->addChangeListener(this);
    mainView.addAndMakeVisible(newFileContainerUI);
    newFileContainerUI->init();
    updateFileContainerUILayout();

}

void FileContainerManagerUI::updateFileContainerUILayout(){
    std::cout << "updateFileContainerUILayout size: " << fileContainerUIs.size() << std::endl;
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
    
    if (fileContainerUIs.size() > 0)
        mainView.setBounds(0, 0, getWidth(), fileContainerUIs.getLast()->getBottom());
    
}

void FileContainerManagerUI::changeListenerCallback(ChangeBroadcaster *source){
    
    // Attempt to cast the changebroadcaster as a FileContainerUI
    FileContainerUI* fileContainerUI = dynamic_cast<FileContainerUI*>(source);
    
    // If successful, update our layout
    if (fileContainerUI != nullptr ) {
        updateFileContainerUILayout();
    }
}


