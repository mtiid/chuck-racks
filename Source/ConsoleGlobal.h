//
//  ConsoleGlobal.hpp
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 3/12/16.
//
//

#ifndef ConsoleGlobal_hpp
#define ConsoleGlobal_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"

class ConsoleGlobal
{
static ConsoleGlobal * instance;
    
public:
    ConsoleGlobal() {};
    ~ConsoleGlobal() {};
    
    static ConsoleGlobal * Instance()
    {
        if(instance == NULL)
        {
            instance = new ConsoleGlobal();
        }
        return instance;
    }
    
    void addText(String text)
    {
        fullText = fullText + "\n" + text;
        if(consoleComponent != NULL)
        {
            consoleComponent->setText(fullText);
        }
    }
    
    void updateText()
    {
        if(consoleComponent != NULL)
        {
            consoleComponent->setText(fullText);
        }
    }
    
    void setConsoleComponent(TextEditor * console)
    {
        consoleComponent = console;
    }
private:
    TextEditor * consoleComponent;
    String fullText;
    
};

#endif /* ConsoleGlobal_hpp */
