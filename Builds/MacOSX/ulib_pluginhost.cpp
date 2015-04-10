//
//  ulib_pluginhost.cpp
//  chuck-vst
//
//  Created by Spencer Salazar on 4/1/15.
//
//

#include "ulib_pluginhost.h"


PluginHostInfo *g_hostInfo = NULL;

CK_DLL_SFUN(pluginhost_getTempo)
{
    RETURN->v_float = g_hostInfo->tempo;
}



t_CKBOOL pluginhost_query( Chuck_DL_Query * QUERY )
{
    g_hostInfo = new PluginHostInfo;
    g_hostInfo->tempo = 120;
    
    QUERY->begin_class(QUERY, "PluginHost", "Object");
    
    QUERY->add_sfun(QUERY, pluginhost_getTempo, "float", "getTempo");
    
    QUERY->end_class(QUERY);
    
    return TRUE;
}

