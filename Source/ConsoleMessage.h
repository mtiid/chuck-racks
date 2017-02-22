/*
  ==============================================================================

    ConsoleMessage.h
    Created: 21 Feb 2017 10:27:44pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#ifndef CONSOLEMESSAGE_H_INCLUDED
#define CONSOLEMESSAGE_H_INCLUDED

#include "JuceHeader.h"

class ConsoleMessage : public Message{
    
public:
    ConsoleMessage(String newText);
    ~ConsoleMessage();
    
private:
    String text;
};



#endif  // CONSOLELISTENER_H_INCLUDED
