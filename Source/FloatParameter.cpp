/*
  ==============================================================================

    FloatParameter.cpp
    Created: 10 Dec 2015 7:06:46pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#include "FloatParameter.h"

FloatParameter::FloatParameter( String parameterID, String name,
                                NormalisableRange<float> normalisableRange,
                                float defaultValue) :
                                AudioProcessorParameterWithID(parameterID, name),
                                range(normalisableRange),
                                defaultValue(defaultValue),
                                value(defaultValue),
                                displayName(name)
{
}

FloatParameter::~FloatParameter(){
    
}

float FloatParameter::getValue() const
{
    return range.convertTo0to1(value);
}

void FloatParameter::setValue(float newValue)
{
    value = range.convertFrom0to1(newValue);
}

float FloatParameter::getValueFrom0to1(){
    return range.convertFrom0to1(value);
}

float FloatParameter::getDefaultValue() const
{
    return defaultValue;
}

void FloatParameter::setName(String newName){
    displayName = newName;
}

String FloatParameter::getName(int /* maximumStringLength */) const
{
    return displayName;
}

String FloatParameter::getLabel() const
{
    return String();
}

float FloatParameter::getValueForText(const String& text) const
{
    return text.getFloatValue();
}
