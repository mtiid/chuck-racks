//
//  FileContainerUI.h
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#ifndef __ChuckRacks__FileContainerUI__
#define __ChuckRacks__FileContainerUI__

#include <stdio.h>
#include "ChuckTokeniser.h"
#include "FileContainerModel.h"
#include "AppViewMode.h"

class FileContainerUI : public Component,
                        private FilenameComponentListener,
                        public Button::Listener
{
    
public:
    FileContainerUI(FileContainerModel* fileContainerModel);
    ~FileContainerUI();
    
    void paint (Graphics& g) override;
    void resized() override;
    
    ScopedPointer<CodeEditorComponent> codeEditor;
    
    void filenameComponentChanged (FilenameComponent*) override;
    void buttonClicked(Button* buttonThatWasPressed) override;
        
private:
    
    ChuckTokeniser ckTokeniser;
    FileContainerModel* mFileContainerModel;
    //FilenameComponent filenameComponent;
    
    ScopedPointer<TextButton> browseCodeButton;
    ScopedPointer<DrawableButton> addShredButton;
    ScopedPointer<DrawableButton> removeShredButton;
    
    ScopedPointer<TextButton> openFileButton;
    ScopedPointer<TextButton> saveFileButton;
    
    
};

#endif /* defined(__ChuckRacks__FileContainerUI__) */

