//
//  ConsoleGlobal.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 3/12/16.
//
//

#include "ConsoleGlobal.h"

ConsoleGlobal * ConsoleGlobal::instance = NULL;

ConsoleGlobal::ConsoleGlobal(){
    
    componentResizer = new ResizableEdgeComponent(this, nullptr, ResizableEdgeComponent::topEdge);
    addAndMakeVisible(componentResizer);
}

ConsoleGlobal::~ConsoleGlobal(){
    
}

void ConsoleGlobal::paint (Graphics& g){
    
}

void ConsoleGlobal::resized(){
    componentResizer->setBounds(getBounds());
    consoleComponent->setBounds(getBounds());
}

void ConsoleGlobal::addText( String text )
{
    if(text.length() > 1)
    {
        fullText = fullText + "\n" + text;
        if( consoleComponent != NULL )
        {
            consoleComponent->setText( fullText );
            consoleComponent->scrollDown();
            consoleComponent->moveCaretToEnd();
        }
    }
}

void ConsoleGlobal::updateText()
{
    if(consoleComponent != NULL)
    {
        consoleComponent->setText( fullText );
        consoleComponent->scrollDown();
        consoleComponent->moveCaretToEnd();
        
    }
}

void ConsoleGlobal::setConsoleComponent(TextEditor * console)
{
    consoleComponent = console;
}
