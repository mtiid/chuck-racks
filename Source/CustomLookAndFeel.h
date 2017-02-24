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
    void drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override;
    void drawTextEditorOutline  (Graphics& g, int width, int height, TextEditor& textEditor) override;
    void drawTableHeaderBackground (Graphics& g, TableHeaderComponent& header) override;
    void drawTableHeaderColumn (Graphics& g, const String& columnName, int /*columnId*/,
                                int width, int height, bool isMouseOver, bool isMouseDown,
                                int columnFlags) override;
    void drawStretchableLayoutResizerBar (Graphics& g, int /*w*/, int /*h*/, bool /*isVerticalBar*/,
                                          bool isMouseOver, bool isMouseDragging) override;
    
     void drawTabButton (TabBarButton&, Graphics&, bool isMouseOver, bool isMouseDown) override;
};

#endif /* defined(__ChuckRacks__CustomLookAndFeel__) */

