//
//  ConsoleGlobal.hpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 3/12/16.
//
//

#ifndef ConsoleGlobal_hpp
#define ConsoleGlobal_hpp

#include <stdio.h>
#include "../JuceLibraryCode/JuceHeader.h"

class ConsoleGlobal : public Component
{
static ConsoleGlobal * instance;
    
public:
    ConsoleGlobal();
    ~ConsoleGlobal();
    
    static ConsoleGlobal * Instance()
    {
        if(instance == NULL)
        {
            instance = new ConsoleGlobal();
        }
        return instance;
    }
    
    void addText( String text );
    void updateText();
    void setConsoleComponent(TextEditor * console);

    void paint (Graphics& g) override;
    void resized() override;
    
private:
    ScopedPointer<ResizableEdgeComponent> componentResizer;
    TextEditor * consoleComponent;
    String fullText;
    
};

#endif /* ConsoleGlobal_hpp */
