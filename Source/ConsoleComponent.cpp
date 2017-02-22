/*
  ==============================================================================

    ConsoleComponent.cpp
    Created: 11 Feb 2017 9:53:14pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#include "ConsoleComponent.h"
#include "CustomLookAndFeel.h"
ConsoleComponent::ConsoleComponent(){
    consoleEditor = new TextEditor("ConsoleEditor");
    addAndMakeVisible(consoleEditor);
    
    // Set up console component
    //consoleEditor->setReadOnly(true);
    consoleEditor->setMultiLine(true);
    consoleEditor->setCaretVisible(false);
    consoleEditor->setScrollbarsShown(true);
    consoleEditor->setScrollBarThickness(10);
    consoleEditor->setColour(TextEditor::backgroundColourId, Colour(38, 40, 49));
}

ConsoleComponent::~ConsoleComponent(){
}

void ConsoleComponent::paint (Graphics& g){
    g.fillAll(Colours::red);
}

void ConsoleComponent::resized(){
    consoleEditor->setBounds(0, 0, getWidth(), getHeight());
}

void ConsoleComponent::addText( String text )
{
    if(text.length() > 1)
    {
        fullText = fullText + "\n" + text;
        if( consoleEditor != NULL )
        {
            consoleEditor->setText( fullText );
            consoleEditor->scrollDown();
            consoleEditor->moveCaretToEnd();
        }
    }
}

void ConsoleComponent::updateText()
{
    if(consoleEditor != NULL)
    {
        consoleEditor->setText( fullText );
        consoleEditor->scrollDown();
        consoleEditor->moveCaretToEnd();
        
    }
}

void ConsoleComponent::handleMessage (const Message & message){
    
}

/*void ConsoleComponent::consoleMessageCallback(String msg){
    addText(msg);
}*/
