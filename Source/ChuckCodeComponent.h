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
    
    
    void filenameComponentChanged (FilenameComponent*) override;
    void buttonClicked(Button* buttonThatWasPressed) override;
    
    ChuckCodeModel* getChuckCodeModel(){return mChuckCodeModel;};
private:
    
    ChuckCodeModel* mChuckCodeModel;
    ChuckTokeniser ckTokeniser;
    ScopedPointer<CodeEditorComponent> codeEditor;

    ScopedPointer<TextButton> browseCodeButton;
    ScopedPointer<DrawableButton> addShredButton;
    ScopedPointer<DrawableButton> removeShredButton;
    
    ScopedPointer<TextButton> openFileButton;
    ScopedPointer<TextButton> saveFileButton;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChuckCodeComponent);

};

#endif /* defined(__ChuckRacks__FileContainerUI__) */

