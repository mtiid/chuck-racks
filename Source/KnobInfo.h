//
//  Knob.h
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/24/15.
//
//

#ifndef ChuckRacks_KnobInfo_h
#define ChuckRacks_KnobInfo_h



enum knobType
{
    linear=0,
    logarithmic,
    exponential
};

struct KnobInfo
{
    KnobInfo():value01(0.5),type(linear) {};
    float value01;
    float valueConverted;
    knobType type;
    int knobId;
    bool active;
    
    
};


#endif
