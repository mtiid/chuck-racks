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

class PluginHostInfo
{
public:
    PluginHostInfo();
    
    float tempo;
    int currentBeat;
    int beatsPerMeasure;
    
    float quarterLength;
    float eighthLength;
    float sixteenthLength;
    
    
    Chuck_Event *playEvent;
    Chuck_Event *sixteenthEvent;
    Chuck_Event *beatStartEvent;
    Chuck_Event *stopEvent;
    
    void setTempo(float newTempo);

    
    void broadcastPlayEvent();
    void broadcastStopEvent();
    void broadcastBeatStartEvent();
    void broadcast16thHit();
    
    float previousTempo;
    float previousBar;
    bool wasPlaying;
    int current16th;
    float positionInBeat;
    float absolutePosition;
    float lastBar;
};

extern PluginHostInfo *g_hostInfo;

t_CKBOOL pluginhost_query( Chuck_DL_Query * QUERY );


#endif /* defined(__chuck_vst__ulib_pluginhost__) */
