/*
  ==============================================================================

    FloatParameter.cpp
    Created: 13 Dec 2016 11:07:00am
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#include "FloatParameter.h"

FloatParameter::FloatParameter(std::function<void(float)> myFunction,
                               String parameterID,
                               String name,
                               NormalisableRange<float> normalisableRange,
                               float defaultValue) : AudioProcessorParameterWithID(parameterID, name),
                                range(normalisableRange),
                                defaultValue(defaultValue),
                                value(defaultValue)
{
    setValueCallback = myFunction;
}

FloatParameter::~FloatParameter(){
    
}

float FloatParameter::getValue() const
{
    return (value);
}

void FloatParameter::setValue(float newValue)
{
    value = range.convertFrom0to1(newValue);
    setValueCallback(value);
}

float FloatParameter::getValueFrom0to1() const
{
    return range.convertFrom0to1(value);
}

float FloatParameter::getDefaultValue() const
{
    return defaultValue;
}

String FloatParameter::getName(int maxLength) const
{
    return name;
}

String FloatParameter::getLabel() const
{
    return String();
}

float FloatParameter::getValueForText(const juce::String &text) const
{
    return text.getFloatValue();
}

