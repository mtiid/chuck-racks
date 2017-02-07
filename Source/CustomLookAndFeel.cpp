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
    
    Colour bgDark(38, 40, 49);
    Colour bgLight(100, 106, 127);
    
    Colour customGreen(62, 172, 133);

    // Window
    this->setColour(ScrollBar::trackColourId, Colours::red);
    this->setColour(TabbedButtonBar::tabTextColourId, Colour(38, 40, 49));
    
    // Buttons
    this->setColour(TextButton::buttonColourId, Colours::black.withAlpha(0.2f));
    this->setColour(TextButton::textColourOffId, Colour(220, 220, 220));
    
    //TextEditor
    this->setColour(TextEditor::highlightColourId, bgLight);
    
    //Table
    this->setColour(TableListBox::backgroundColourId, bgDark);
    
    //Popup Menu
    this->setColour(PopupMenu::backgroundColourId, bgLight);
    this->setColour(PopupMenu::highlightedBackgroundColourId, Colours::black.withAlpha(0.2f));
}

CustomLookAndFeel::~CustomLookAndFeel()
{
    
}

void CustomLookAndFeel::drawButtonBackground (Graphics& g, Button& button, const Colour& backgroundColour,
                                              bool isMouseOverButton, bool isButtonDown)
{
    Colour baseColour (backgroundColour.withMultipliedSaturation (button.hasKeyboardFocus (true) ? 1.3f : 0.9f)
                       .withMultipliedAlpha (button.isEnabled() ? 0.9f : 0.5f));
    
    if (isButtonDown || isMouseOverButton)
        baseColour = baseColour.contrasting (isButtonDown ? 0.4f : 0.3f);
    
    const bool flatOnLeft   = button.isConnectedOnLeft();
    const bool flatOnRight  = button.isConnectedOnRight();
    const bool flatOnTop    = button.isConnectedOnTop();
    const bool flatOnBottom = button.isConnectedOnBottom();
    
    const float width  = button.getWidth() - 1.0f;
    const float height = button.getHeight() - 1.0f;
    
    if (width > 0 && height > 0)
    {
        const float cornerSize = jmin (15.0f, jmin (width, height) * 0.15f);
        const float lineThickness = cornerSize * 0.1f;
        const float halfThickness = lineThickness * 0.5f;
        
        Path outline;
        outline.addRoundedRectangle (0.5f + halfThickness, 0.5f + halfThickness, width - lineThickness, height - lineThickness,
                                     cornerSize, cornerSize,
                                     ! (flatOnLeft  || flatOnTop),
                                     ! (flatOnRight || flatOnTop),
                                     ! (flatOnLeft  || flatOnBottom),
                                     ! (flatOnRight || flatOnBottom));
        
        const Colour outlineColour (button.findColour (button.getToggleState() ? TextButton::textColourOnId
                                                       : TextButton::textColourOffId));
        
        g.setColour (baseColour);
        g.fillPath (outline);
        
        if (! button.getToggleState())
        {
            g.setColour (outlineColour);
            //g.strokePath (outline, PathStrokeType (lineThickness));
        }
    }
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
    g.fillAll(Colour(100, 106, 127));
    
    Rectangle<int> r (header.getLocalBounds());
    
    g.setColour(Colour(40, 43, 34));
    g.drawRect(r, 1);
    
    for (int i = header.getNumColumns (true); --i >= 0;)
        g.fillRect (header.getColumnPosition (i).removeFromRight (1));
}

void CustomLookAndFeel::drawTableHeaderColumn (Graphics& g, const String& columnName, int columnId,
                                               int width, int height, bool isMouseOver, bool isMouseDown,
                                               int columnFlags)
{
    
    Rectangle<int> area (width, height);
    area.reduce (4, 0);
    
    g.setColour (Colours::black);
    g.setFont (Font (height * 0.5f, Font::bold));
    if(columnId == 1){
        g.drawFittedText (columnName, area, Justification::centred, 1);
    }else{
        g.drawFittedText (columnName, area, Justification::centredLeft, 1);
    }
}
