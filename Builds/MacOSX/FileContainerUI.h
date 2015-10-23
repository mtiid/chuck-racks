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
    
    
    void init();
    
    void paint (Graphics& g);
    
    ChuckTokeniser ckTokeniser;
    FileContainerModel* m_fileContainerModel;
    FilenameComponent filenameComponent;
    
    ScopedPointer<CodeEditorComponent> codeEditor;
    
    void timerCallback();
    
    void filenameComponentChanged (FilenameComponent*) override;
    
    int bottom;
    void updateBottom();
    
    ScopedPointer<TextButton> addShredButton;
    ScopedPointer<TextButton> browseCodeButton;
    ScopedPointer<TextButton> removeShredButton;
    
    void buttonClicked(Button* buttonThatWasPressed);
    String lastFileLoaded;
    
    std::vector<ScopedPointer<Slider>> knobs;
    const int knobAmount=8;
    const int knobsPerRow=4;
    const int knobStartX=200;
    const int knobStartY=10;
    const int knobSize=40;
    const int knobSpacing =10;

    void sliderValueChanged (Slider* slider);

    
};