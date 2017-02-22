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
        if(instance == nullptr)
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
    TextEditor * consoleComponent;
    String fullText;
    
    ScopedPointer<ResizableEdgeComponent> consoleResizer;
    ScopedPointer<ComponentBoundsConstrainer> consoleContrainer;
    
};

#endif /* ConsoleGlobal_hpp */
