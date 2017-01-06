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
    void prepareToPlay (double sampleRate, int samplesPerBlock);
    void releaseResources();

    void processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages);

    //==============================================================================
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //==============================================================================
    const String getName() const;

    int getNumParameters();

    float getParameter (int index);
    void setParameter (int index, float newValue);

    const String getParameterName (int index);
    const String getParameterText (int index);

    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;

    bool acceptsMidi() const;
    bool producesMidi() const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;

    //==============================================================================
    int getNumPrograms();
    int getCurrentProgram();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String& newName);

    //==============================================================================
    void getStateInformation (MemoryBlock& destData);
    void setStateInformation (const void* data, int sizeInBytes);
    
    
    //*********************************************************************

    
    FileContainerManagerModel* getFileContainerManagerModel(){return fileContainerManagerModel;};
    static AudioProcessor * getProcessor() { return processorInstance; };
    
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChuckRacksAudioProcessor)
    
    chuck_inst *ck;
    float *input_buffer;
    float *output_buffer;
    
    MidiBuffer midiInputBuffer;
    MidiBuffer midiOutputBuffer;
    
    AudioPlayHead::CurrentPositionInfo lastPosInfo;
    ScopedPointer<CodeEditorDemo> codeEditorDemo;

    FileContainerManagerModel * fileContainerManagerModel;
    static AudioProcessor * processorInstance;

};

#endif  // PLUGINPROCESSOR_H_INCLUDED
