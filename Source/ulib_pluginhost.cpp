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

    currentSixteenth=-1;

    previousBar=-1;

    tempo = 120;
    
    wholeLength = 240/tempo;
    halfLength = 120/tempo;
    quarterLength = 60/tempo;
    eighthLength = 30/tempo;
    sixteenthLength = 15/tempo;

    tempMidiBuffer = new MidiBuffer();
    
    sampleRate = 44100; //default
    
    position = positionInBar = positionInBeat = 0;
    lastBarStartPosition = 0;
    
    timeSigNumerator = 1;
    timeSigDenominator = 1;
}


PluginHostInfo *g_hostInfo = NULL;


void PluginHostInfo::broadcastPlayEvent()
{
    if(g_hostInfo->playEvent != NULL)
        g_hostInfo->playEvent->broadcast();
}

void PluginHostInfo::broadcastNextBarEvent()
{
    if(g_hostInfo->nextBarEvent != NULL)
        g_hostInfo->nextBarEvent->broadcast();
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
    tempo = newTempo;
    wholeLength = 240/tempo;
    halfLength = 120/tempo;
    quarterLength = 60/tempo;
    eighthLength = 30/tempo;
    sixteenthLength = 15/tempo;
}

void PluginHostInfo::broadcastQuarterHit()
{
    if(g_hostInfo->quarterEvent!= NULL)
        g_hostInfo->quarterEvent->broadcast();
}

void PluginHostInfo::broadcastEighthHit()
{
    if(g_hostInfo->eighthEvent!= NULL)
        g_hostInfo->eighthEvent->broadcast();
}

void PluginHostInfo::broadcastSixteenthHit()
{
    if(g_hostInfo->sixteenthEvent != NULL)
        g_hostInfo->sixteenthEvent->broadcast();
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

CK_DLL_SFUN(pluginhost_nextBar)
{
    if(g_hostInfo->nextBarEvent == NULL)
    {
        g_hostInfo->nextBarEvent = new Chuck_Event();
        initialize_object(g_hostInfo->nextBarEvent, &t_event);
    }

    RETURN->v_object = g_hostInfo->nextBarEvent;
}

CK_DLL_SFUN(pluginhost_quarter)
{
    if(g_hostInfo->quarterEvent == NULL)
    {
        g_hostInfo->quarterEvent = new Chuck_Event();
        initialize_object(g_hostInfo->quarterEvent, &t_event);
    }

    RETURN->v_object = g_hostInfo->quarterEvent;
}

CK_DLL_SFUN(pluginhost_eighth)
{
    if(g_hostInfo->eighthEvent == NULL)
    {
        g_hostInfo->eighthEvent = new Chuck_Event();
        initialize_object(g_hostInfo->eighthEvent, &t_event);
    }

    RETURN->v_object = g_hostInfo->eighthEvent;
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

CK_DLL_SFUN(pluginhost_wholeDur)
{
    RETURN->v_dur = g_hostInfo->wholeLength * g_hostInfo->sampleRate;
}

CK_DLL_SFUN(pluginhost_halfDur)
{
    RETURN->v_dur = g_hostInfo->halfLength * g_hostInfo->sampleRate;
}

CK_DLL_SFUN(pluginhost_quarterLength)
{
    RETURN->v_float = g_hostInfo->quarterLength;
}

CK_DLL_SFUN(pluginhost_quarterDur)
{
    RETURN->v_dur = g_hostInfo->quarterLength * g_hostInfo->sampleRate;
}


CK_DLL_SFUN(pluginhost_eighthLength)
{
    RETURN->v_float = g_hostInfo->eighthLength;
}

CK_DLL_SFUN(pluginhost_eighthDur)
{
    RETURN->v_dur = g_hostInfo->eighthLength * g_hostInfo->sampleRate;
}

CK_DLL_SFUN(pluginhost_sixteenthLength)
{
    RETURN->v_float = g_hostInfo->sixteenthLength;
}

CK_DLL_SFUN(pluginhost_sixteenthDur)
{
    RETURN->v_dur = g_hostInfo->sixteenthLength * g_hostInfo->sampleRate;
}


CK_DLL_SFUN(pluginhost_positionInBeat)
{
    RETURN->v_float = g_hostInfo->positionInBeat;
}

CK_DLL_SFUN(pluginhost_positionInBar)
{
    RETURN->v_float = g_hostInfo->positionInBar;
}

CK_DLL_SFUN(pluginhost_position)
{
    RETURN->v_float = g_hostInfo->position;
}

CK_DLL_SFUN(pluginhost_lastBarPosition)
{
    RETURN->v_float = g_hostInfo->lastBarStartPosition;
}

CK_DLL_SFUN(pluginhost_timeSigNumerator)
{
    RETURN->v_int = g_hostInfo->timeSigNumerator;
}

CK_DLL_SFUN(pluginhost_timeSigDenominator)
{
    RETURN->v_int = g_hostInfo->timeSigDenominator;
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

    int pos = 0;

    if(!g_hostInfo->midiInputBufferP->isEmpty())
    {
        if(iterator.getNextEvent(messageIn, pos))
        {
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

        }
        g_hostInfo->tempMidiBuffer->clear();

        while( iterator.getNextEvent(messageIn, pos) )
        {
            g_hostInfo->tempMidiBuffer->addEvent(messageIn, pos); //adds all events not used in here to temp buffer
        }
        g_hostInfo->midiInputBufferP->swapWith( *g_hostInfo->tempMidiBuffer ); //swaps old buffer with new buffer without used event
    }

    OBJ_MEMBER_INT(_msg, MidiMsg_offset_data1) = byte1;
    OBJ_MEMBER_INT(_msg, MidiMsg_offset_data2) = byte2;
    OBJ_MEMBER_INT(_msg, MidiMsg_offset_data3) = byte3;

    RETURN->v_int = ret_val;
}

CK_DLL_SFUN(pluginhost_sendMidi)
{
    Chuck_Object *_msg = GET_NEXT_OBJECT(ARGS);

    unsigned char byte1 = OBJ_MEMBER_INT(_msg, MidiMsg_offset_data1);
    unsigned char byte2 = OBJ_MEMBER_INT(_msg, MidiMsg_offset_data2);
    unsigned char byte3 = OBJ_MEMBER_INT(_msg, MidiMsg_offset_data3);

    juce::MidiMessage midiMessage(byte1, byte2, byte3);
    g_hostInfo->midiOutputBufferP->addEvent( midiMessage, 0); //TODO: find if there's a way of getting a close sample instead of using 0

    RETURN->v_int = 1;
}

t_CKBOOL pluginhost_query( Chuck_DL_Query * QUERY )
{
    g_hostInfo = new PluginHostInfo;
    g_hostInfo->playEvent = NULL;
    g_hostInfo->stopEvent = NULL;
    g_hostInfo->quarterEvent = NULL;
    g_hostInfo->eighthEvent = NULL;
    g_hostInfo->sixteenthEvent = NULL;
    g_hostInfo->nextBarEvent = NULL;
    g_hostInfo->midiEvent = NULL;

    QUERY->begin_class(QUERY, "PluginHost", "Object");
    QUERY->doc_class(QUERY, "Class for interacting with plugin host. ");

    //events
    
    QUERY->add_sfun(QUERY, pluginhost_onPlay, "Event", "onPlay"); //return type, chuck function name
    
    QUERY->add_sfun(QUERY, pluginhost_onStop, "Event", "onStop");
    
    QUERY->add_sfun(QUERY, pluginhost_onMidi, "Event", "onMidi");
    
    QUERY->add_sfun(QUERY, pluginhost_nextBar, "Event", "nextBar");
    
    QUERY->add_sfun(QUERY, pluginhost_quarter,"Event", "nextQuarter");
    
    QUERY->add_sfun(QUERY, pluginhost_eighth,"Event", "nextEighth");
    
    QUERY->add_sfun(QUERY, pluginhost_sixteenth,"Event", "nextSixteenth");
    
    
    //durs and lengths
    
    QUERY->add_sfun(QUERY, pluginhost_quarterDur, "dur", "quarterDur");
    QUERY->doc_func(QUERY, "Returns the duration of a quarter note as a dur. ");
    
    QUERY->add_sfun(QUERY, pluginhost_wholeDur, "dur", "wholeDur");
    QUERY->doc_func(QUERY, "Returns the duration of a whole note as a dur. ");
    
    QUERY->add_sfun(QUERY, pluginhost_halfDur, "dur", "halfDur");
    QUERY->doc_func(QUERY, "Returns the duration of a half note as a dur. ");
    
    QUERY->add_sfun(QUERY, pluginhost_eighthDur, "dur", "eighthDur");
    QUERY->doc_func(QUERY, "Returns the duration of an eighth note as a dur. ");
    
    QUERY->add_sfun(QUERY, pluginhost_sixteenthDur, "dur", "sixteenthDur");
    QUERY->doc_func(QUERY, "Returns the duration of an sixteenth note as a dur. ");
    
    
    
    QUERY->add_sfun(QUERY, pluginhost_quarterLength, "float", "quarterLength");
    QUERY->doc_func(QUERY, "Returns the length of a quarter notes in seconds at the current BPM. ");
    
    QUERY->add_sfun(QUERY, pluginhost_eighthLength, "float", "eighthLength");
    QUERY->doc_func(QUERY, "Returns the length of a 8th notes in seconds at the current BPM. ");
    
    QUERY->add_sfun(QUERY, pluginhost_sixteenthLength, "float", "sixteenthLength");
    QUERY->doc_func(QUERY, "Returns the length of a 16th notes in seconds at the current BPM. ");
    
    
    //other

    QUERY->add_sfun(QUERY, pluginhost_getTempo, "float", "getTempo"); //return type, chuck function name
    QUERY->doc_func(QUERY, "Returns current tempo in BPM.");

    QUERY->add_sfun(QUERY, pluginhost_setTempo, "float", "setTempo"); //return type, chuck function name
    QUERY->add_arg(QUERY, "float", "tempo");
    

    QUERY->add_sfun(QUERY, pluginhost_isPlaying, "int", "isPlaying");
    QUERY->doc_func(QUERY, "Returns a 1 if the host is playing. Otherwise it returns 0. ");

    QUERY->add_sfun(QUERY, pluginhost_positionInBeat, "float", "posInBeat"); //returns a value between 0 and 0.9999 for the position in the beat. It can be used for finer subdivisions than 16ths.
    QUERY->add_sfun(QUERY, pluginhost_positionInBar, "float", "posInBar");
    
    QUERY->add_sfun(QUERY, pluginhost_position, "float", "pos");
    
    QUERY->add_sfun(QUERY, pluginhost_lastBarPosition, "float", "posLastBarStart");
    
    QUERY->add_sfun(QUERY, pluginhost_timeSigNumerator, "int", "timeSigUpper");
    
    QUERY->add_sfun(QUERY, pluginhost_timeSigDenominator, "int", "timeSigLower");
    

    QUERY->add_sfun(QUERY, pluginhost_recvMidi, "int", "recvMidi");
    QUERY->add_arg(QUERY, "MidiMsg", "msg");

    QUERY->add_sfun(QUERY, pluginhost_sendMidi, "int", "sendMidi");
    QUERY->add_arg(QUERY, "MidiMsg", "msg");


    QUERY->end_class(QUERY);

    return TRUE;
}

