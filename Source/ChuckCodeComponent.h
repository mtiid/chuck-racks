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
#include "ChuckCodeModel.h"

class ChuckCodeComponent : public Component,
                        private FilenameComponentListener,
                        public Button::Listener
{
    
public:
    ChuckCodeComponent(ChuckCodeModel* chuckCodeModel);
    ~ChuckCodeComponent();
    
    void paint (Graphics& g) override;
    void resized() override;
    
    ScopedPointer<CodeEditorComponent> codeEditor;
    
    void filenameComponentChanged (FilenameComponent*) override;
    void buttonClicked(Button* buttonThatWasPressed) override;
        
private:
    
    ChuckTokeniser ckTokeniser;
    ChuckCodeModel* mChuckCodeModel;
    //FilenameComponent filenameComponent;
    
    ScopedPointer<TextButton> browseCodeButton;
    ScopedPointer<DrawableButton> addShredButton;
    ScopedPointer<DrawableButton> removeShredButton;
    
    ScopedPointer<TextButton> openFileButton;
    ScopedPointer<TextButton> saveFileButton;
};

#endif /* defined(__ChuckRacks__FileContainerUI__) */

