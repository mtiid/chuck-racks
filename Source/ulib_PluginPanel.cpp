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
    //RETURN->v_float = g_hostInfo->tempo;
    
    //std::string filename = SHRED->code->filename;
    //std::string arg1 = SHRED->args[0];
    
    t_CKINT containerId = GET_NEXT_INT(ARGS);
    
    t_CKINT whichKnob = GET_NEXT_INT(ARGS);
    
    
    //if (g_pluginPanel->fileContainerManager!=nullptr) {
    //    t_CKINT shred_id = SHRED->xid;
    //}
    
    /*
    std::string containerIdInShred = SHRED->args[0];
    int containerIdInShredAsInt = std::strtol(containerIdInShred.c_str(), NULL, 10);
    */ // I don't remember what this is for... Maybe for a newer version of chucklib? Ask Spencer
    
    
    FileContainerModel * thisFileContainer = g_pluginPanel->fileContainerManager->findFileContainer(containerId);
    
    if (thisFileContainer != nullptr)
    {
        //RETURN->v_float = 1.0;
        RETURN->v_float = thisFileContainer->knobParameters.at(whichKnob)->getValue();
    }
    else
    {
        DBG("File container called from PluginPanel.getValue is null!");
         RETURN->v_float = 0.0;
    }
    
   
}

// chuck object and functions definitions

t_CKBOOL pluginPanel_query( Chuck_DL_Query * QUERY)
{
    
    g_pluginPanel = new PluginPanel;
    
    QUERY->begin_class(QUERY, "PluginPanel", "Object");
    
    QUERY->add_sfun(QUERY, pluginPanel_getValue, "float", "getValue"); //return type, chuck function name
    
    QUERY->add_arg(QUERY, "int", "containerId"); // first argument
    
    QUERY->add_arg(QUERY, "int", "whichKnob");
    QUERY->end_class(QUERY);
    
    return TRUE;

    
    
}




