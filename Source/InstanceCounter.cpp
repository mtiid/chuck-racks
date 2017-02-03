//
//  InstanceCounter.cpp
//  ChuckRacks
//
//  Created by Jacob Penn on 2/2/17.
//
//

#include "InstanceCounter.h"

instanceCounter::instanceCounter()
{
    mCount = 0;
}

instanceCounter::~instanceCounter()
{
    
}

void instanceCounter::incrementCount()
{
    mCount++;
}

void instanceCounter::decrementCount()
{
    mCount--;
}

int instanceCounter::getCount()
{
    return mCount;
}