//
//  FileContainerManagerUI.h
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "../JuceLibraryCode/JuceHeader.h"


#ifndef __ChuckPluginTest4__FileContainerManagerUI__
#define __ChuckPluginTest4__FileContainerManagerUI__

#include <stdio.h>
#include "FileContainerManagerModel.h"


class FileContainerManagerUI : public Component, public ButtonListener, public Timer, Slider::Listener
{
public:
    
    
    FileContainerManagerUI(FileContainerManagerModel* managerModel);
    ~FileContainerManagerUI();
    
    void paint(Graphics& g);
    
    FileContainerManagerModel* m_managerModel;
    
    void timerCallback();
    void buttonClicked(Button* buttonThatWasPressed);
    void sliderValueChanged (Slider* slider);
    std::vector<ScopedPointer<FileContainerUI>> fileContainerUIs;
    void updateTopPositions();
    void init();
    
};

#endif /* defined(__ChuckPluginTest4__FileContainerManagerUI__) */
