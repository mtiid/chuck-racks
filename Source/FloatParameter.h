/*
  ==============================================================================

    FloatParameter.h
    Created: 13 Dec 2016 11:07:00am
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#ifndef FLOATPARAMETER_H_INCLUDED
#define FLOATPARAMETER_H_INCLUDED

#include "JuceHeader.h"

class FloatParameter : public AudioProcessorParameterWithID
{
    
public:
    FloatParameter(std::function<void(float)> myFunction,
                   String parameterID,
                   String name,
                   NormalisableRange<float> normalisableRange,
                   float defaultValue);
    
    ~FloatParameter();
    
    float getValue() const override;
    float getValueFrom0to1() const;
    
    void setValue(float newValue) override;
    float getDefaultValue() const override;
    String getName(int maxLength) const override;
    String getLabel() const override;
    float getValueForText(const String& text) const override;

    NormalisableRange<float> range;
    
private:
    float defaultValue, value;
    std::function<void(float)> setValueCallback;
    
};




#endif  // FLOATPARAMETER_H_INCLUDED
