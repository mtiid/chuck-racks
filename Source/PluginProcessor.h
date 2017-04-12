/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include "libchuck.h"
#include "CodeEditorDemo.h"
#include "ChuckCodeModelManager.h"
#include "Defines.h"
#include "FloatParameter.h"
#include "Counter.h"
//==============================================================================
/**
*/
class ChuckRacksAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    ChuckRacksAudioProcessor();
    ~ChuckRacksAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    #ifndef JucePlugin_PreferredChannelConfigurations
     bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    #endif
    
    //void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages) override;
    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;
    
    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    const String getInputChannelName (int channelIndex) const override;
    const String getOutputChannelName (int channelIndex) const override;
    bool isInputChannelStereoPair (int index) const override;
    bool isOutputChannelStereoPair (int index) const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    
    //*********************************************************************

    
    ChuckCodeModelManager* getChuckCodeModelManager(){return chuckCodeModelManager;};
    AudioProcessor * getProcessor() { return this; };
    
    std::map<int, String>* getParameterListModel(){return parameterListModel;};
    bool mapNewParam();
    void updateParamNames(int num, String newText);
    float getParamValue(String paramName);
    
    void cleanUp();
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChuckRacksAudioProcessor)
    
    chuck_inst *ck = NULL;
    float *input_buffer = NULL;
    float *output_buffer = NULL;
    
    MidiBuffer midiInputBuffer;
    MidiBuffer midiOutputBuffer;
    
    AudioPlayHead::CurrentPositionInfo lastPosInfo;

    ChuckCodeModelManager*  chuckCodeModelManager = NULL;
    std::map<int, String>* parameterListModel;

    //AudioProcessorValueTreeState parameters;
    
    SharedResourcePointer<Counter> instanceCounter;
    int thisInstanceCount;
    float lastBarStart;
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
