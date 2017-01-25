//
//  CustomLookAndFeel.cpp
//  ChuckRacks
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

void CustomLookAndFeel::drawTableHeaderBackground (Graphics& g, TableHeaderComponent& header)
{
    Rectangle<int> r (header.getLocalBounds());
    
    g.setColour (Colours::black.withAlpha (0.5f));
    g.fillRect (r.removeFromBottom (1));
    
    g.setColour (Colour(50, 53, 64));
    g.fillRect (r);
    
    g.setColour (Colours::black.withAlpha (0.5f));
    
    for (int i = header.getNumColumns (true); --i >= 0;)
        g.fillRect (header.getColumnPosition (i).removeFromRight (1));
}
