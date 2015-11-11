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

class FileContainerUI : public Component,
                        private FilenameComponentListener,
                        public ButtonListener,
                        public Timer,
                        public Slider::Listener,
                        public ChangeBroadcaster
{
public:
    FileContainerUI(FileContainerModel* fileContainerModel);
    ~FileContainerUI();
    
    void init();
    void paint (Graphics& g);
   
    
    ScopedPointer<CodeEditorComponent> codeEditor;
    
    void timerCallback();
    void filenameComponentChanged (FilenameComponent*) override;
    void buttonClicked(Button* buttonThatWasPressed);
    
    bool isShowingCodeEditor(){return mCodeEditorVisible;};
    
private:
    
    ChuckTokeniser ckTokeniser;
    FileContainerModel* mFileContainerModel;
    FilenameComponent filenameComponent;
    
    String lastFileLoaded;
    
    ScopedPointer<DrawableButton> showHideCodeEditorButton;
    ScopedPointer<TextButton> browseCodeButton;
    ScopedPointer<DrawableButton> addShredButton;
    ScopedPointer<DrawableButton> removeShredButton;
    
    std::vector<Slider *> knobs;
    const int knobAmount=8;
    const int knobsPerRow=4;
    const int knobStartX=200;
    const int knobStartY=10;
    const int knobSize=40;
    const int knobSpacing =10;
    
    void sliderValueChanged (Slider* slider);
    void updateSize();
    
    bool mCodeEditorVisible;
    
};