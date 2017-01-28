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
#include "FileContainerManagerModel.h"
#include "Defines.h"
#include "FloatParameter.h"
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

    
    FileContainerManagerModel* getFileContainerManagerModel(){return fileContainerManagerModel;};
    AudioProcessor * getProcessor() { return this; };
    
    void updateParamNames(int num, String newText);
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChuckRacksAudioProcessor)
    
    chuck_inst *ck;
    float *input_buffer;
    float *output_buffer;
    
    MidiBuffer midiInputBuffer;
    MidiBuffer midiOutputBuffer;
    
    AudioPlayHead::CurrentPositionInfo lastPosInfo;

    FileContainerManagerModel*  fileContainerManagerModel;
 
};

#endif  // PLUGINPROCESSOR_H_INCLUDED
