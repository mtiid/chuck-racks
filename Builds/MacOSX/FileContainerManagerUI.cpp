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

FileContainerManagerUI::~FileContainerManagerUI()
{
    
    
    
}

void FileContainerManagerUI::init(){
    fileContainerUIs.clear();
    for(int i =0; i< m_managerModel->fileContainerModels.size(); i++)
    {
        //fileContainerUIs.pop_back();
        FileContainerUI* newFileContainerUI = new FileContainerUI(m_managerModel->fileContainerModels[i]);
        addAndMakeVisible(newFileContainerUI);
        newFileContainerUI->setBounds(0, 0, getWidth(), getHeight());
        fileContainerUIs.push_back(newFileContainerUI);
    }
    
    updateTopPositions();
}

void FileContainerManagerUI::paint(Graphics& g){
    g.fillAll(Colours::red);
}

void FileContainerManagerUI::timerCallback()
{
    
}

void FileContainerManagerUI::sliderValueChanged (Slider* slider)
{
    
}

void FileContainerManagerUI::buttonClicked(Button* buttonThatWasPressed)
{
    
}

void FileContainerManagerUI::updateTopPositions()
{
    if(fileContainerUIs[0]!=nullptr)
    {
        fileContainerUIs[0]->setTopLeftPosition(0, 0);
        for (int i=1; i<fileContainerUIs.size(); i++)
        {
            fileContainerUIs[i]->setTopLeftPosition(0, fileContainerUIs[i-1]->getBottom());
            std::cout << i << " " fileContainerUIs[i]->getY() << std::endl;
        }
    }
}