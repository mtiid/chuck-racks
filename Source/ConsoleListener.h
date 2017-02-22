/*
  ==============================================================================

    ConsoleListener.h
    Created: 21 Feb 2017 10:27:44pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#ifndef CONSOLELISTENER_H_INCLUDED
#define CONSOLELISTENER_H_INCLUDED

#include "JuceHeader.h"

class ConsoleListener{
    
public:
    ConsoleListener();
    virtual ~ConsoleListener();
    
    virtual void consoleMessageCallback(String msg);
    
private:
    
};



#endif  // CONSOLELISTENER_H_INCLUDED
