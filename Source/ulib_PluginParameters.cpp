//
//  ulib_PluginParameters.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//



#include "ulib_PluginParameters.h"
#include "chuck_instr.h"
#include "chuck_type.h"
#include "chuck_vm.h"
#include <string>

PluginParameters *g_pluginParameters = NULL;


PluginParameters::PluginParameters()
{

}

PluginParameters::~PluginParameters()
{
    
}

//in-chuck functions implementations

CK_DLL_SFUN(pluginParameters_getValue)
{
    
    Chuck_String* paramName = (Chuck_String*)GET_NEXT_OBJECT(ARGS);

    ChuckRacksAudioProcessor* proc = static_cast<ChuckRacksAudioProcessor*>(g_pluginParameters->chuckCodeModelManager->processor);
    
    float val = proc->getParamValue( String(paramName->str) );
    
    RETURN->v_float = val;
}

// chuck object and functions definitions

t_CKBOOL pluginParameters_query( Chuck_DL_Query * QUERY)
{
    
    g_pluginParameters = new PluginParameters;
    
    QUERY->begin_class(QUERY, "PluginParameters", "Object");
    
    QUERY->add_sfun(QUERY, pluginParameters_getValue, "float", "getValue"); //return type, chuck function name

    QUERY->add_arg(QUERY, "string", "paramName");
    QUERY->end_class(QUERY);
    
    return TRUE;

    
    
}




