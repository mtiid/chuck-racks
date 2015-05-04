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
    
    fileContainerUIs.clear();
    for(int i =0; i< m_managerModel->fileContainerModels.size(); i++)
    {
        fileContainerUIs.pop_back();
        fileContainerUIs[i]=new FileContainerUI(m_managerModel->fileContainerModels[i]);
        addAndMakeVisible(fileContainerUIs[i]);
        
    }
    updateTopPositions();
}

FileContainerManagerUI::~FileContainerManagerUI()
{
    
    
    
}

void FileContainerManagerUI::timerCallback()
{
    
}

void FileContainerManagerUI::sliderValueChanged (Slider* slider)
{
    
}

void FileContainerManagerUI::updateTopPositions()
{
    fileContainerUIs[0]->setTopLeftPosition(0, 0);
    for (int i=0; i<fileContainerUIs.size(); i++)
    {
        fileContainerUIs[i]->setTopLeftPosition(0, fileContainerUIs[i-1]->getBottom());
    }
}