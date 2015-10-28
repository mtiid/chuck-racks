//
//  ulib_pluginhost.cpp
//  chuck-vst
//
//  Created by Spencer Salazar on 4/1/15.
//
//

#include "ulib_pluginhost.h"
#include "chuck_instr.h"
#include "chuck_type.h"


// TODO: this is really hacky
// these should be declared in the chuck_lang.h header
// and imported that way
extern t_CKUINT MidiMsg_offset_data1;
extern t_CKUINT MidiMsg_offset_data2;
extern t_CKUINT MidiMsg_offset_data3;

PluginHostInfo::PluginHostInfo()
{
    wasPlaying=false;
    current16th=-1;
    previousBar=-1;
    
    tempo=120;
    quarterLength=60/tempo;
    eighthLength=30/tempo;
    sixteenthLength=15/tempo;
}


PluginHostInfo *g_hostInfo = NULL;


void PluginHostInfo::broadcastPlayEvent()
{
    if(g_hostInfo->playEvent != NULL)
        g_hostInfo->playEvent->broadcast();
}

void PluginHostInfo::broadcastBeatStartEvent()
{
    if(g_hostInfo->beatStartEvent != NULL)
        g_hostInfo->beatStartEvent->broadcast();
}

void PluginHostInfo::broadcastStopEvent()
{
    if(g_hostInfo->stopEvent != NULL)
        g_hostInfo->stopEvent->broadcast();
}

void PluginHostInfo::broadcastMidiEvent()
{
    if(g_hostInfo->midiEvent != NULL)
        g_hostInfo->midiEvent->broadcast();
}

void PluginHostInfo::setTempo(float newTempo)
{
    tempo=newTempo;
    quarterLength=60/tempo;
    eighthLength=30/tempo;
    sixteenthLength=15/tempo;
}

void PluginHostInfo::broadcast16thHit()
{
    
    if(g_hostInfo->sixteenthEvent != NULL)
        g_hostInfo->sixteenthEvent->broadcast();

}

void PluginHostInfo::getMidiMessage(MidiMessage message)
{
    //Chuck_Object *_msg = GET_NEXT_OBJECT(ARGS);
    
    // get next msg from JUCE
    // if no msg, return 0
    // if msg return 1
    //unsigned char byte1 = 0x90;
    //unsigned char byte2 = 60;
    //unsigned char byte3 = 100;
    
    //OBJ_MEMBER_INT(_msg, MidiMsg_offset_data1) = byte1;
    //OBJ_MEMBER_INT(_msg, MidiMsg_offset_data2) = byte2;
    //OBJ_MEMBER_INT(_msg, MidiMsg_offset_data3) = byte3;
    
    //OBJ_MEMBER_INT(_msg, 0)=    message.getRawData();

    
    //RETURN->v_int = 1;

    
}


CK_DLL_SFUN(pluginhost_getTempo)
{
    RETURN->v_float = g_hostInfo->tempo;
}

CK_DLL_SFUN(pluginhost_setTempo)
{
    t_CKFLOAT tempo = GET_NEXT_FLOAT(ARGS);
    
    //JUCE::SetTEMPO(tempo);
    
    
    RETURN->v_float = g_hostInfo->tempo;
}

CK_DLL_SFUN(pluginhost_onPlay)
{
    if(g_hostInfo->playEvent == NULL)
    {
        g_hostInfo->playEvent = new Chuck_Event();
        initialize_object(g_hostInfo->playEvent, &t_event);
    }
    
    RETURN->v_object = g_hostInfo->playEvent;
}

CK_DLL_SFUN(pluginhost_onStop)
{
    if(g_hostInfo->stopEvent == NULL)
    {
        g_hostInfo->stopEvent = new Chuck_Event();
        initialize_object(g_hostInfo->stopEvent, &t_event);
    }
    
    RETURN->v_object = g_hostInfo->stopEvent;
}

CK_DLL_SFUN(pluginhost_onBeatStart)
{
    if(g_hostInfo->beatStartEvent == NULL)
    {
        g_hostInfo->beatStartEvent = new Chuck_Event();
        initialize_object(g_hostInfo->beatStartEvent, &t_event);
    }
    
    RETURN->v_object = g_hostInfo->beatStartEvent;
}


CK_DLL_SFUN(pluginhost_sixteenth)
{
    if(g_hostInfo->sixteenthEvent == NULL)
    {
        g_hostInfo->sixteenthEvent = new Chuck_Event();
        initialize_object(g_hostInfo->sixteenthEvent, &t_event);
    }
    
    RETURN->v_object = g_hostInfo->sixteenthEvent;
}


CK_DLL_SFUN(pluginhost_isPlaying)
{
    if (g_hostInfo->wasPlaying) {
        RETURN->v_int = 1;
    }
    else
    {
        RETURN->v_int = 0;
    }
    
}

CK_DLL_SFUN(pluginhost_sixteenthLength)
{
    RETURN->v_float = g_hostInfo->sixteenthLength;
}

CK_DLL_SFUN(pluginhost_eightLength)
{
    RETURN->v_float = g_hostInfo->eighthLength;
}

CK_DLL_SFUN(pluginhost_quarterLength)
{
    RETURN->v_float = g_hostInfo->quarterLength;
}


CK_DLL_SFUN(pluginhost_positionInBeat)
{
    RETURN->v_float = g_hostInfo->positionInBeat;
}


CK_DLL_SFUN(pluginhost_onMidi)
{
    if(g_hostInfo->midiEvent == NULL)
    {
        g_hostInfo->midiEvent = new Chuck_Event();
        initialize_object(g_hostInfo->midiEvent, &t_event);
    }
    
    RETURN->v_object = g_hostInfo->midiEvent;
}



CK_DLL_SFUN(pluginhost_recvMidi)
{
    Chuck_Object *_msg = GET_NEXT_OBJECT(ARGS);
    
    unsigned char byte1 = 0;
    unsigned char byte2 = 0;
    unsigned char byte3 = 0;
    int ret_val = 0;

    // get next msg from JUCE
    MidiBuffer::Iterator iterator(*g_hostInfo->midiInputBufferP);
    MidiMessage messageIn;
    //int position = 0;
    //if(iterator.getNextEvent(messageIn, g_hostInfo->midiOutputBufferPos))
    //{
    int pos = 0;
    if(iterator.getNextEvent(messageIn, pos))
    {
//        iterator.getNextEvent(messageIn, g_hostInfo->midiOutputBufferPos);
        
        const uint8 *midivals = messageIn.getRawData();
        int datasize = messageIn.getRawDataSize();
        //DBG(String(*messageIn.getRawData()));
        
        // if no msg, return 0
        // if msg return 1
        
        
        
        if(datasize>0)
            byte1 = midivals[0];
        if(datasize>1)
            byte2 = midivals[1];
        if(datasize>2)
            byte3 = midivals[2];
        
        ret_val = 1;
        
        g_hostInfo->midiInputBufferP->clear(); //fix this! Just eliminate first message in midiInpufBuffer
        
        
    }
    
    OBJ_MEMBER_INT(_msg, MidiMsg_offset_data1) = byte1;
    OBJ_MEMBER_INT(_msg, MidiMsg_offset_data2) = byte2;
    OBJ_MEMBER_INT(_msg, MidiMsg_offset_data3) = byte3;
    
    RETURN->v_int = ret_val;
}

CK_DLL_SFUN(pluginhost_sendMidi)
{
    Chuck_Object *_msg = GET_NEXT_OBJECT(ARGS);
    
    // get next msg from JUCE
    
    // if no msg, return 0
    // if msg return 1
    
    unsigned char byte1 = OBJ_MEMBER_INT(_msg, MidiMsg_offset_data1);
    unsigned char byte2 = OBJ_MEMBER_INT(_msg, MidiMsg_offset_data2);
    unsigned char byte3 = OBJ_MEMBER_INT(_msg, MidiMsg_offset_data3);
    
    
    
    RETURN->v_int = 1;
}


t_CKBOOL pluginhost_query( Chuck_DL_Query * QUERY )
{
    g_hostInfo = new PluginHostInfo;
    g_hostInfo->playEvent = NULL;
    g_hostInfo->stopEvent = NULL;
    g_hostInfo->sixteenthEvent = NULL;
    g_hostInfo->beatStartEvent = NULL;
    g_hostInfo->midiEvent = NULL;

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
    

    QUERY->add_sfun(QUERY, pluginhost_sixteenthLength, "float", "sixteenthLength");
    QUERY->doc_func(QUERY, "Returns the length of a 16th notes in seconds at the current BPM. ");
    
    QUERY->add_sfun(QUERY, pluginhost_sixteenth,"Event", "sixteenth");
    
    
    QUERY->add_sfun(QUERY, pluginhost_isPlaying, "int", "isPlaying");
    QUERY->doc_func(QUERY, "Returns a 1 if the host is playing. Otherwise it returns 0. ");

    QUERY->add_sfun(QUERY, pluginhost_positionInBeat, "float", "positionInBeat"); //returns a value between 0 and 0.9999 for the position in the beat. It can be used for finer subdivisions than 16ths.
    
    


    QUERY->add_sfun(QUERY, pluginhost_recvMidi, "int", "recvMidi");
    QUERY->add_arg(QUERY, "MidiMsg", "msg");
    
    QUERY->add_sfun(QUERY, pluginhost_sendMidi, "int", "sendMidi");
    QUERY->add_arg(QUERY, "MidiMsg", "msg");
    
    
    
    
    QUERY->end_class(QUERY);
    
    return TRUE;
}

