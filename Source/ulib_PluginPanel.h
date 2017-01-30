//
//  ulib_PluginPanel.h
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//



#ifndef __ChuckRacks__ulib_PluginPanel__
#define __ChuckRacks__ulib_PluginPanel__

#include <stdio.h>
#include "chuck_dl.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "FileContainerManagerModel.h"
#include "PluginProcessor.h"


class PluginPanel
{
public:
 
    PluginPanel();
    ~PluginPanel();
    
    ScopedPointer<FileContainerManagerModel> fileContainerManager;
};


extern PluginPanel *g_pluginPanel;

t_CKBOOL pluginPanel_query( Chuck_DL_Query * QUERY );


#endif /*defined(__ChuckRacks__ulib_PluginPanel__)*/
