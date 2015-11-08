//
//  CustomLookAndFeel.cpp
//  ChuckPluginTest4
//
//  Created by Jordan Hochenbaum on 10/23/15.
//
//

#include "CustomLookAndFeel.h"

CustomLookAndFeel::CustomLookAndFeel()
{
    
    // Window
    this->setColour(ScrollBar::trackColourId, Colours::red);
    this->setColour(TabbedButtonBar::tabTextColourId, Colour(38, 40, 49));
    
}

CustomLookAndFeel::~CustomLookAndFeel()
{
    
}



void CustomLookAndFeel::drawTextEditorOutline (Graphics& g, int width, int height, TextEditor& textEditor)
{
    if (textEditor.isEnabled())
    {
        
        g.setColour (textEditor.findColour (TextEditor::outlineColourId));
        g.drawRect (0, 0, width, height);
        
        g.setOpacity (1.0f);
        const Colour shadowColour (textEditor.findColour (TextEditor::shadowColourId));
        drawBevel (g, 0, 0, width, height + 2, 3, shadowColour, shadowColour);
    }
}