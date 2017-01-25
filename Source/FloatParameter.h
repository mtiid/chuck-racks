/*
  ==============================================================================

    FloatParameter.h
    Created: 10 Dec 2015 7:06:46pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#ifndef FLOATPARAMETER_H_INCLUDED
#define FLOATPARAMETER_H_INCLUDED
#include "JuceHeader.h"

class FloatParameter : public AudioProcessorParameterWithID
{
public:
    FloatParameter( String parameterID, String name,
                         NormalisableRange<float> normalisableRange,
                         float defaultValue);
    
    ~FloatParameter();
    
    float getValue() const override;
    float getValueFrom0to1();

    void setValue(float newValue) override;
    float getDefaultValue() const override;
    void setName(String newName);
    String getName(int /* maximumStringLength */) const override;
    String getLabel() const override;
    float getValueForText(const String& text) const override;
    
    NormalisableRange<float> range;

private:
    String displayName;
    float defaultValue, value;
};



#endif  // FLOATPARAMETER_H_INCLUDED
