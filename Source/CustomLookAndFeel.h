//
//  CustomLookAndFeel.h
//  ChuckRacks
//
//  Created by Jordan Hochenbaum on 10/23/15.
//
//

#ifndef __ChuckRacks__CustomLookAndFeel__
#define __ChuckRacks__CustomLookAndFeel__

#include "../JuceLibraryCode/JuceHeader.h"

class CustomLookAndFeel : public LookAndFeel_V3
{
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel();
    
private:
    void drawTextEditorOutline  (Graphics& g, int width, int height, TextEditor& textEditor) override;    
};

#endif /* defined(__ChuckRacks__CustomLookAndFeel__) */

