//
//  ConsoleGlobal.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 3/12/16.
//
//

#include "ConsoleGlobal.h"

ConsoleGlobal * ConsoleGlobal::instance = nullptr;

ConsoleGlobal::ConsoleGlobal(){
    consoleContrainer = new ComponentBoundsConstrainer();
    consoleResizer = new ResizableEdgeComponent(this, consoleContrainer, ResizableEdgeComponent::topEdge);
    addAndMakeVisible(consoleResizer);
    consoleContrainer->setSizeLimits(getParentWidth(), 50, getParentWidth(), 150);
}

ConsoleGlobal::~ConsoleGlobal(){
    
}

void ConsoleGlobal::paint (Graphics& g){
    
}

void ConsoleGlobal::resized(){
    //consoleComponent->setBounds(consol)
    if (consoleComponent != nullptr) {
        consoleComponent->setBounds(getLocalBounds());
        consoleResizer->setBounds(0,
                                  consoleComponent->getBounds().getY()-consoleComponent->getHeight(),
                                  getLocalBounds().getWidth(),
                                  8);
    }
    
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
