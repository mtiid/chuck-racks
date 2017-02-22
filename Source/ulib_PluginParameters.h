//
//  ulib_PluginParameters.h
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//



#ifndef __ChuckRacks__ulib_PluginParameters__
#define __ChuckRacks__ulib_PluginParameters__

#include <stdio.h>
#include "chuck_dl.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "ChuckCodeModelManager.h"
#include "PluginProcessor.h"


class PluginParameters
{
public:
 
    PluginParameters();
    ~PluginParameters();
    
    ScopedPointer<ChuckCodeModelManager> chuckCodeModelManager;
};


extern PluginParameters *g_pluginParameters;

t_CKBOOL pluginParameters_query( Chuck_DL_Query * QUERY );


#endif /*defined(__ChuckRacks__ulib_PluginParameters__)*/
