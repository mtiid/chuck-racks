/*
  ==============================================================================

    ConsoleComponent.h
    Created: 11 Feb 2017 9:53:14pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#ifndef CONSOLECOMPONENT_H_INCLUDED
#define CONSOLECOMPONENT_H_INCLUDED

#include "JuceHeader.h"

class ConsoleComponent : public Component
{
    
public:
    ConsoleComponent();
    ~ConsoleComponent();
    
    void paint (Graphics& g) override;
    void resized() override;
    
    void addText( String text );
    void updateText();
    
private:
    
    ScopedPointer<TextEditor> consoleEditor;
    String fullText;

};



#endif  // CONSOLECOMPONENT_H_INCLUDED
