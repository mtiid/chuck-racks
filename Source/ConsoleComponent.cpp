/*
  ==============================================================================

    ConsoleComponent.cpp
    Created: 11 Feb 2017 9:53:14pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#include "ConsoleComponent.h"
#include "CustomLookAndFeel.h"

//ConsoleComponent* ConsoleComponent::instance = nullptr;
juce_ImplementSingleton (ConsoleComponent);

ConsoleComponent::ConsoleComponent(){
    //consoleEditor = new TextEditor("ConsoleEditor");
    //addAndMakeVisible(consoleEditor);
    
    // Set up console component
    //consoleEditor->setReadOnly(true);
    /*consoleEditor->setMultiLine(true);
    consoleEditor->setCaretVisible(false);
    consoleEditor->setScrollbarsShown(true);
    consoleEditor->setScrollBarThickness(10);
    consoleEditor->setColour(TextEditor::backgroundColourId, Colour(38, 40, 49));*/
}

ConsoleComponent::~ConsoleComponent(){
}

void ConsoleComponent::paint (Graphics& g){
}

void ConsoleComponent::resized(){
    consoleEditor->setBounds(0, 0, getWidth(), getHeight());
}

void ConsoleComponent::addText( String text )
{
    if(text.isNotEmpty())
    {
        fullText = "\n" + text;
        //fullText = fullText + "\n" + text;
        if( consoleEditor != nullptr )
        {
            consoleEditor->insertTextAtCaret( fullText );
            //consoleEditor->scrollDown();
            //consoleEditor->moveCaretToEnd();
        }
    }
}

void ConsoleComponent::updateText()
{
    if(consoleEditor != nullptr)
    {
        consoleEditor->setText( fullText );
        consoleEditor->scrollDown();
        consoleEditor->moveCaretToEnd();
        
    }
}

void ConsoleComponent::setConsoleComponent(TextEditor * console)
{
    consoleEditor = console;
}
