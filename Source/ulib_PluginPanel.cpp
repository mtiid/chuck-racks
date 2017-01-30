//
//  ulib_PluginPanel.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//



#include "ulib_PluginPanel.h"
#include "chuck_instr.h"
#include "chuck_type.h"
#include "chuck_vm.h"
#include <string>

PluginPanel *g_pluginPanel = NULL;


PluginPanel::PluginPanel()
{

}

PluginPanel::~PluginPanel()
{
    
}

//in-chuck functions implementations

CK_DLL_SFUN(pluginPanel_getValue)
{
    
    Chuck_String* paramName = (Chuck_String*)GET_NEXT_OBJECT(ARGS);

    ChuckRacksAudioProcessor* proc = static_cast<ChuckRacksAudioProcessor*>(g_pluginPanel->fileContainerManager->processor);
    
    float val = proc->getParamValue( String(paramName->str) );
    DBG( val );
    
    RETURN->v_float = val;
}

// chuck object and functions definitions

t_CKBOOL pluginPanel_query( Chuck_DL_Query * QUERY)
{
    
    g_pluginPanel = new PluginPanel;
    
    QUERY->begin_class(QUERY, "PluginPanel", "Object");
    
    QUERY->add_sfun(QUERY, pluginPanel_getValue, "float", "getValue"); //return type, chuck function name

    QUERY->add_arg(QUERY, "string", "paramName");
    QUERY->end_class(QUERY);
    
    return TRUE;

    
    
}




