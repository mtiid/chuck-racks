//
//  ulib_pluginhost.h
//  chuck-vst
//
//  Created by Spencer Salazar on 4/1/15.
//
//

#ifndef __chuck_vst__ulib_pluginhost__
#define __chuck_vst__ulib_pluginhost__

#include <stdio.h>
#include "chuck_dl.h"
#include "../JuceLibraryCode/JuceHeader.h"


class PluginHostInfo
{
public:
    PluginHostInfo();

    float tempo;
    int currentBeat;
    int beatsPerMeasure;

    float wholeLength;
    float halfLength;
    float quarterLength;
    float eighthLength;
    float sixteenthLength;


    Chuck_Event *playEvent;
    Chuck_Event *quarterEvent;
    Chuck_Event *eighthEvent;
    Chuck_Event *sixteenthEvent;
    Chuck_Event *nextBarEvent;
    Chuck_Event *stopEvent;
    Chuck_Event *midiEvent;


    void setTempo(float newTempo);

    void broadcastPlayEvent();
    void broadcastStopEvent();
    //void broadcastBeatStartEvent();
    void broadcastNextBarEvent();

    void broadcastQuarterHit();
    void broadcastEighthHit();
    void broadcastSixteenthHit();

    void broadcastMidiEvent();
    void getMidiMessage(MidiMessage message);

    float previousTempo;
    float previousBar;
    bool wasPlaying;

    int currentSixteenth;

    float positionInBeat;
    float positionInBar;
    float position;
    float lastBarStartPosition;
    
    int timeSigNumerator;
    int timeSigDenominator;
    
    float sampleRate;

    MidiBuffer* midiInputBufferP;
    MidiBuffer* midiOutputBufferP;
    MidiBuffer* tempMidiBuffer;

    int midiOutputBufferPos;

};

extern PluginHostInfo *g_hostInfo;

t_CKBOOL pluginhost_query( Chuck_DL_Query * QUERY );


#endif /* defined(__chuck_vst__ulib_pluginhost__) */
