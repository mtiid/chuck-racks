//
//  Counter.cpp
//  ChuckRacks
//
//  Created by Jacob Penn on 2/2/17.
//
//

#include "Counter.h"

Counter::Counter()
{
    mCount = 0;
}

Counter::~Counter()
{
    
}

void Counter::incrementCount()
{
    mCount++;
}

void Counter::decrementCount()
{
    mCount--;
}

int Counter::getCount()
{
    return mCount;
}