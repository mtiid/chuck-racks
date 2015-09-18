//
//  FileContainerManagerUI.cpp
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "FileContainerManagerUI.h"


FileContainerManagerUI::FileContainerManagerUI(FileContainerManagerModel* managerModel):scrollbar(true)
{
    m_managerModel=managerModel;
    
    addAndMakeVisible (scrollbar);
    scrollbar.setRangeLimits (0.0,1.0,dontSendNotification);
    scrollbar.setAutoHide (false);
    scrollbar.addListener (this);
    
}

/*
void setRange (Range<double> newRange)
{
    visibleRange = newRange;
    scrollbar.setCurrentRange (visibleRange);
    updateCursorPosition();
    repaint();
}
 */

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

void FileContainerManagerUI::scrollBarMoved (ScrollBar* scrollBarThatHasMoved, double newRangeStart)
{
    //if (scrollBarThatHasMoved == &scrollbar)
      //  if (! (isFollowingTransport && transportSource.isPlaying()))
        //    setRange (visibleRange.movedToStartAt (newRangeStart));
}

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
    }
}