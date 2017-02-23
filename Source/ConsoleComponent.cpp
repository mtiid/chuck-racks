/*
  ==============================================================================

    ConsoleComponent.cpp
    Created: 11 Feb 2017 9:53:14pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#include "ConsoleComponent.h"
#include "CustomLookAndFeel.h"

juce_ImplementSingleton (ConsoleComponent);

ConsoleComponent::ConsoleComponent(){
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
        if( consoleEditor != nullptr )
            consoleEditor->insertTextAtCaret( fullText );
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
