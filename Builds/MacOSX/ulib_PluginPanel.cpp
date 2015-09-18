//
//  ulib_PluginPanel.cpp
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "ulib_PluginPanel.h"
#include "chuck_instr.h"
#include "chuck_type.h"

/*
t_CKBOOL pluginhost_query( Chuck_DL_Query * QUERY )
{
    g_hostInfo = new PluginHostInfo;
    g_hostInfo->playEvent = NULL;
    g_hostInfo->stopEvent = NULL;
    g_hostInfo->sixteenthEvent = NULL;
    g_hostInfo->beatStartEvent = NULL;
    
    QUERY->begin_class(QUERY, "PluginHost", "Object");
    QUERY->doc_class(QUERY, "Class for interacting with plugin host. ");
    
    
    QUERY->add_sfun(QUERY, pluginhost_getTempo, "float", "getTempo"); //return type, chuck function name
    QUERY->doc_func(QUERY, "Returns current tempo in BPM.");
    
    QUERY->add_sfun(QUERY, pluginhost_setTempo, "float", "setTempo"); //return type, chuck function name
    
    QUERY->add_arg(QUERY, "float", "tempo"); // first argument
    
    QUERY->add_sfun(QUERY, pluginhost_onPlay, "Event", "onPlay"); //return type, chuck function name
    
    QUERY->add_sfun(QUERY, pluginhost_onStop, "Event", "onStop");
    
    QUERY->add_sfun(QUERY, pluginhost_onBeatStart, "Event", "onBeat");
    
    QUERY->add_sfun(QUERY, pluginhost_onMidi, "Event", "onMidi");
    
    QUERY->add_sfun(QUERY, pluginhost_recvMidi, "int", "recvMidi");
    QUERY->add_arg(QUERY, "MidiMsg", "msg");
    
    QUERY->add_sfun(QUERY, pluginhost_sendMidi, "int", "sendMidi");
    QUERY->add_arg(QUERY, "MidiMsg", "msg");
    
    QUERY->add_sfun(QUERY, pluginhost_sixteenthLength, "float", "sixteenthLength");
    QUERY->doc_func(QUERY, "Returns the length of a 16th notes in seconds at the current BPM. ");
    
    QUERY->add_sfun(QUERY, pluginhost_sixteenth,"Event", "sixteenth");
    
    
    QUERY->add_sfun(QUERY, pluginhost_isPlaying, "int", "isPlaying");
    QUERY->doc_func(QUERY, "Returns a 1 if the host is playing. Otherwise it returns 0. ");
    
    QUERY->add_sfun(QUERY, pluginhost_positionInBeat, "float", "positionInBeat"); //returns a value between 0 and 0.9999 for the position in the beat. It can be used for finer subdivisions than 16ths.
    
    
    
    
    QUERY->end_class(QUERY);
    
    return TRUE;
}
 */
