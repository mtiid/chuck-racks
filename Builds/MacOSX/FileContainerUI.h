//
//  FileContainerUI.h
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#ifndef __ChuckPluginTest4__FileContainerUI__
#define __ChuckPluginTest4__FileContainerUI__

#include <stdio.h>
#include "ChuckTokeniser.h"
#include "FileContainerModel.h"

#endif /* defined(__ChuckPluginTest4__FileContainerUI__) */

class FileContainerUI : public Component, private FilenameComponentListener, public ButtonListener, public Timer, Slider::Listener
{
public:
    FileContainerUI(FileContainerModel* fileContainerModel);
    ~FileContainerUI();
    
    void paint (Graphics& g);
    
    ChuckTokeniser ckTokeniser;
    FileContainerModel* m_fileContainerModel;
    FilenameComponent filenameComponent;
    
    ScopedPointer<CodeEditorComponent> codeEditor;
    
    void timerCallback();
    
    void sliderValueChanged (Slider* slider);
    void buttonClicked(Button* buttonThatWasPressed);
    void filenameComponentChanged (FilenameComponent*) override;
    
    int bottom;
    void updateBottom();    
    
};