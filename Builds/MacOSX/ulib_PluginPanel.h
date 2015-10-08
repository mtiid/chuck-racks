//
//  ulib_PluginPanel.h
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#ifndef __ChuckPluginTest4__ulib_PluginPanel__
#define __ChuckPluginTest4__ulib_PluginPanel__

#include <stdio.h>
#include "chuck_dl.h"
#include "../JuceLibraryCode/JuceHeader.h"


class PluginPanel
{
public:
    static PluginPanel * instance;
    
    PluginPanel()
    {
        if (instance==nullptr)
        {
            instance = new PluginPanel();
        }
        else
        {
            std::cout<<"Tried to create another instance of PluginPanel! It's a singleton!"<<std::endl;
        }
        
    }
    
    ~PluginPanel();
    
    
    
};

#endif /* defined(__ChuckPluginTest4__ulib_PluginPanel__) */
