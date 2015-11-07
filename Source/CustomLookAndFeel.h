//
//  CustomLookAndFeel.h
//  ChuckPluginTest4
//
//  Created by Jordan Hochenbaum on 10/23/15.
//
//

#ifndef __ChuckPluginTest4__CustomLookAndFeel__
#define __ChuckPluginTest4__CustomLookAndFeel__

#include "JuceHeader.h"

class CustomLookAndFeel : public LookAndFeel_V3
{
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel();
    
private:
    void drawTextEditorOutline  (Graphics& g, int width, int height, TextEditor& textEditor) override;    
};

#endif /* defined(__ChuckPluginTest4__CustomLookAndFeel__) */
