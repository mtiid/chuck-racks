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

class ConsoleComponent :    public Component
{
    
public:
    
    //static ConsoleComponent * instance;
    
    ConsoleComponent();
    ~ConsoleComponent();
    
    /*static ConsoleComponent * Instance()
    {
        if(instance == nullptr)
        {
            instance = new ConsoleComponent();
        }
        return instance;
    }*/
    
    void paint (Graphics& g) override;
    void resized() override;
    
    void addText( String text );
    void updateText();
    
    void setConsoleComponent(TextEditor * console);
    
    juce_DeclareSingleton (ConsoleComponent, false);
    
private:
    TextEditor* consoleEditor;
    String fullText;

};



#endif  // CONSOLECOMPONENT_H_INCLUDED
