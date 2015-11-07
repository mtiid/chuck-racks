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
    Colour backgroundGrey = Colour::fromRGB(209,209,209);
    Colour lightGrey = Colour::fromRGB(99,99,99);
    Colour darkGrey = Colour::fromRGB(61,61,61);
    
    //buttons
    this->setColour(TextButton::buttonColourId, Colours::whitesmoke);
    
    //sliders
    this->setColour(Slider::thumbColourId, Colours::yellow);
    this->setColour(Slider::backgroundColourId, backgroundGrey);
    this->setColour(Slider::textBoxTextColourId, Colours::black);
    this->setColour(Slider::textBoxHighlightColourId, Colours::black);
    this->setColour(Slider::textBoxOutlineColourId, Colours::black);
    
    //other
    this->setColour(TextEditor::outlineColourId, Colours::black);
    this->setColour(TextEditor::focusedOutlineColourId, Colours::black);
    this->setColour(TextEditor::backgroundColourId, backgroundGrey);
    this->setColour(ListBox::backgroundColourId, backgroundGrey);
    this->setColour(ListBox::outlineColourId, Colours::black);
    
    //Window
    this->setColour(ScrollBar::trackColourId, Colours::red);
    
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