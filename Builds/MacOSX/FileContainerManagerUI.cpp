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
    scrollableView.setBounds(0,0, getWidth(), getHeight());
    addAndMakeVisible(scrollableView);

    scrollableView.setViewedComponent(&mainView);

    
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
        mainView.addAndMakeVisible(newFileContainerUI);
        addAndMakeVisible(newFileContainerUI);
    
        newFileContainerUI->setBounds(100, 100, getWidth()-200, getHeight()-200);
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

/*void FileContainerManagerUI::scrollBarMoved (ScrollBar* scrollBarThatHasMoved, double newRangeStart)
{
    //if (scrollBarThatHasMoved == &scrollbar)
      //  if (! (isFollowingTransport && transportSource.isPlaying()))
        //    setRange (visibleRange.movedToStartAt (newRangeStart));
}*/

void FileContainerManagerUI::updateTopPositions()
{
    if(fileContainerUIs[0]!=nullptr)
    {
        fileContainerUIs[0]->setTopLeftPosition(0, 0);
        for (int i=1; i<fileContainerUIs.size(); i++)
        {
            fileContainerUIs[i]->setTopLeftPosition(0, fileContainerUIs[i-1]->getBottom());
            std::cout << i << " " << fileContainerUIs[i]->getY() << std::endl;
        }
        
        mainView.setBounds(0, 0, getWidth(), 100*fileContainerUIs.size());
        
        repaint();
    }
}