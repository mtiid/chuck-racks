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
    
    //mainView = new Component();
    //mainView.setBounds(0, 0, getWidth(), getHeight());
}


FileContainerManagerUI::~FileContainerManagerUI()
{
    
    
    
}


void FileContainerManagerUI::paint(Graphics& g){
    
    g.fillAll(Colours::grey);
    g.setColour(Colours::red);
    g.drawRect(getLocalBounds(), 1);
    
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
        fileContainerUIs.push_back(newFileContainerUI);
        mainView.addAndMakeVisible(newFileContainerUI);
        newFileContainerUI->setBounds(0, (getHeight()-200)*i, getWidth(), getHeight()-200);
        newFileContainerUI->init();
    }
    
    mainView.setBounds(0, 0, getWidth()-18, (getHeight()-200)*fileContainerUIs.size());
    /*if(scrollableView.isVerticalScrollBarShown()){
        mainView.setBounds(0, 0, getWidth()-18, (getHeight()-200)*fileContainerUIs.size());
    }*/
    //updateTopPositions();
    
    
}

/*void FileContainerManagerUI::updateTopPositions()
{
    if(fileContainerUIs[0]!=nullptr)
    {
        fileContainerUIs[0]->setTopLeftPosition(0, 0);
        for (int i=1; i<fileContainerUIs.size(); i++)
        {
            fileContainerUIs[i]->setTopLeftPosition(0, fileContainerUIs[i-1]->getBottom());
            std::cout << i << " " << fileContainerUIs[i]->getY() << std::endl;
        }
        
        mainView.setBounds(0, 0, getWidth(), (getHeight()-200)*fileContainerUIs.size());
        repaint();
    }
}*/

void FileContainerManagerUI::timerCallback()
{
    
}

void FileContainerManagerUI::sliderValueChanged (Slider* slider)
{
    
}

void FileContainerManagerUI::buttonClicked(Button* buttonThatWasPressed)
{
    
}

