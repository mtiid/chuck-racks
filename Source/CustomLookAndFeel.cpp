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
    
    Colour crGreen(62, 172, 133);

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
    this->setColour(TableListBox::outlineColourId, Colours::black);
    
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

void CustomLookAndFeel::drawStretchableLayoutResizerBar (Graphics& g, int /*w*/, int /*h*/, bool /*isVerticalBar*/,
                                 bool isMouseOver, bool isMouseDragging)
{
    if (isMouseOver || isMouseDragging)
        g.fillAll (Colour(100, 106, 127).withAlpha (0.6f));
}

void CustomLookAndFeel::drawTabButton (TabBarButton& button, Graphics& g, bool isMouseOver, bool isMouseDown)
{
    const Rectangle<int> activeArea (button.getActiveArea());
    
    const TabbedButtonBar::Orientation o = button.getTabbedButtonBar().getOrientation();
    
    const Colour bkg (button.getTabBackgroundColour());
    
    if (button.getToggleState())
    {
        g.setColour (bkg);
    }
    else
    {
        Point<int> p1, p2;
        
        switch (o)
        {
            case TabbedButtonBar::TabsAtBottom:   p1 = activeArea.getBottomLeft(); p2 = activeArea.getTopLeft();    break;
            case TabbedButtonBar::TabsAtTop:      p1 = activeArea.getTopLeft();    p2 = activeArea.getBottomLeft(); break;
            case TabbedButtonBar::TabsAtRight:    p1 = activeArea.getTopRight();   p2 = activeArea.getTopLeft();    break;
            case TabbedButtonBar::TabsAtLeft:     p1 = activeArea.getTopLeft();    p2 = activeArea.getTopRight();   break;
            default:                              jassertfalse; break;
        }
        
        g.setColour(bkg.darker(0.3f));
    }
    
    g.fillRect (activeArea);
    
    g.setColour (button.findColour (TabbedButtonBar::tabOutlineColourId));
    
    Rectangle<int> r (activeArea);
    
    if (o != TabbedButtonBar::TabsAtBottom)   g.fillRect (r.removeFromTop (1));
    if (o != TabbedButtonBar::TabsAtTop)      g.fillRect (r.removeFromBottom (1));
    if (o != TabbedButtonBar::TabsAtRight)    g.fillRect (r.removeFromLeft (1));
    if (o != TabbedButtonBar::TabsAtLeft)     g.fillRect (r.removeFromRight (1));
    
    const float alpha = button.isEnabled() ? ((isMouseOver || isMouseDown) ? 1.0f : 0.8f) : 0.3f;
    
    Colour col (bkg.contrasting().withMultipliedAlpha (alpha));
    
    if (TabbedButtonBar* bar = button.findParentComponentOfClass<TabbedButtonBar>())
    {
        TabbedButtonBar::ColourIds colID = button.isFrontTab() ? TabbedButtonBar::frontTextColourId
        : TabbedButtonBar::tabTextColourId;
        
        if (bar->isColourSpecified (colID))
            col = bar->findColour (colID);
        else if (isColourSpecified (colID))
            col = findColour (colID);
    }
    
    const Rectangle<float> area (button.getTextArea().toFloat());
    
    float length = area.getWidth();
    float depth  = area.getHeight();
    
    if (button.getTabbedButtonBar().isVertical())
        std::swap (length, depth);
    
    TextLayout textLayout;
    createTabTextLayout (button, length, depth, col, textLayout);
    
    AffineTransform t;
    
    switch (o)
    {
        case TabbedButtonBar::TabsAtLeft:   t = t.rotated (float_Pi * -0.5f).translated (area.getX(), area.getBottom()); break;
        case TabbedButtonBar::TabsAtRight:  t = t.rotated (float_Pi *  0.5f).translated (area.getRight(), area.getY()); break;
        case TabbedButtonBar::TabsAtTop:
        case TabbedButtonBar::TabsAtBottom: t = t.translated (area.getX(), area.getY()); break;
        default:                            jassertfalse; break;
    }
    
    g.addTransform (t);
    textLayout.draw (g, Rectangle<float> (length, depth));
}
