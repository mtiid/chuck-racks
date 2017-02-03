/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic startup code for a Juce application.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ulib_pluginhost.h"
#include "ulib_PluginPanel.h"

//AudioProcessor * ChuckRacksAudioProcessor::processorInstance = NULL;

//==============================================================================
ChuckRacksAudioProcessor::ChuckRacksAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (BusesProperties()
                    #if ! JucePlugin_IsMidiEffect
                     #if ! JucePlugin_IsSynth
                      .withInput  ("Input",  AudioChannelSet::stereo(), true)
                     #endif
                      .withOutput ("Output", AudioChannelSet::stereo(), true)
                    #endif
                  )//,parameters (*this, nullptr)
#endif

{
    //ConsoleGlobal *ConsoleGlobal::instance = 0;
    
    instanceCount->incrementCount();
    
    mInstaceCount = instanceCount->getCount();
    
    if (mInstaceCount > 1)
    {
        AlertWindow::showMessageBox (AlertWindow::AlertIconType::NoIcon,
                                    "Warning",
                                    "Only a single instance of chuck rack may run at once.",
                                    "Okay",
                                     nullptr);
        
    }

    fprintf(stderr, "ChuckRacksAudioProcessor::ChuckRacksAudioProcessor\n");
    chuck_options options;
    libchuck_options_reset(&options);
    //    options.buffer_size = getBlockSize();
    //    options.adaptive_buffer_size = 0;
    //    options.num_channels = getNumOutputChannels();
    //    options.sample_rate = getSampleRate();
    options.slave = true;
    // hardcode (HACK!)
    options.buffer_size = 512;
    options.adaptive_buffer_size = 0;
    options.num_channels = 2;
    options.sample_rate = 44100;
    
    //TODO: check if a valid instance of chuck is running (how do I do this?)
    ck = libchuck_create(&options);
    
    libchuck_add_module(ck, (void*)pluginhost_query);
    libchuck_add_module(ck, (void*)pluginPanel_query);
    
    input_buffer = new float[options.buffer_size*options.num_channels];
    output_buffer = new float[options.buffer_size*options.num_channels];
    
    if (mInstaceCount == 1)
    {
        libchuck_vm_start(ck);
    }
        
    fileContainerManagerModel = new FileContainerManagerModel(ck, this);
    
    g_hostInfo->midiInputBufferP = (&midiInputBuffer);
    g_hostInfo->midiOutputBufferP = (&midiOutputBuffer);
    
    g_pluginPanel->fileContainerManager = fileContainerManagerModel;
    
    for (int i=0; i<512; i++)
    {

        NormalisableRange<float> paramRange(0.0, 1.0, 0.1, 1.0);
        String id = String(i+1);
        FloatParameter* param = new FloatParameter(id, id, paramRange, 1.0);
        addParameter(param);
    }
    
    parameterListModel = new std::map<int, String>;
    //dynamic_cast<FloatParameter*>(getParameters().getUnchecked(0))->setName("Yes!");
}

ChuckRacksAudioProcessor::~ChuckRacksAudioProcessor()
{
    fprintf(stderr, "ChuckRacksAudioProcessor::~ChuckRacksAudioProcessor\n");
    
    libchuck_destroy(ck);
    ck = NULL;
    
    if(input_buffer) { delete[] input_buffer; input_buffer = NULL; }
    if(output_buffer) { delete[] output_buffer; output_buffer = NULL; }
    
}

bool ChuckRacksAudioProcessor::mapNewParam(){
    int numRows = parameterListModel->size();
    if (numRows+1 < 512){
        parameterListModel->insert(std::make_pair(numRows, String("not assigned")));
        return true;
    }else{
        return false;
    }
}

void ChuckRacksAudioProcessor::updateParamNames(int num, String newText){
    FloatParameter* p = dynamic_cast<FloatParameter*>(getParameters().getUnchecked(num));
    p->setName(newText);
    p->setValueNotifyingHost(p->getValue());
    parameterListModel->at(num) = newText;
    updateHostDisplay();
}

float ChuckRacksAudioProcessor::getParamValue(String paramName){
    for (int i=0; i<getParameterListModel()->size(); i++)
    {
        if (getParameterName(i) == paramName)
        {
            return getParameter(i);
        }
    }
    return -1;
}


//==============================================================================
const String ChuckRacksAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

const String ChuckRacksAudioProcessor::getInputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

const String ChuckRacksAudioProcessor::getOutputChannelName (int channelIndex) const
{
    return String (channelIndex + 1);
}

bool ChuckRacksAudioProcessor::isInputChannelStereoPair (int index) const
{
    return true;
}

bool ChuckRacksAudioProcessor::isOutputChannelStereoPair (int index) const
{
    return true;
}

bool ChuckRacksAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool ChuckRacksAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

double ChuckRacksAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChuckRacksAudioProcessor::getNumPrograms()
{
    return 1;
}

int ChuckRacksAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChuckRacksAudioProcessor::setCurrentProgram (int index)
{
}

const String ChuckRacksAudioProcessor::getProgramName (int index)
{
    return String::empty;
}

void ChuckRacksAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ChuckRacksAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ChuckRacksAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChuckRacksAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif

void ChuckRacksAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
//void ChuckRacksAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    // Get current position/time info from host, otherwise set to some default
    AudioPlayHead::CurrentPositionInfo pos;
    if (getPlayHead() != nullptr && getPlayHead()->getCurrentPosition(pos)) {
        lastPosInfo = pos;
    }else{
        lastPosInfo.resetToDefault();
    }
    
    if (lastPosInfo.bpm != g_hostInfo->previousTempo)
    {
        g_hostInfo->setTempo(lastPosInfo.bpm);
    }
    
    if(lastPosInfo.isPlaying&&!g_hostInfo->wasPlaying)
    {
        g_hostInfo->broadcastPlayEvent();
    }
    
    if(!lastPosInfo.isPlaying&&g_hostInfo->wasPlaying)
    {
        g_hostInfo->broadcastStopEvent();
        
    }
    
    g_hostInfo->wasPlaying = lastPosInfo.isPlaying;
    
    
    g_hostInfo->positionInBeat = fmod( pos.ppqPosition,1 );
    
    //DBG(positionInBeat);
    if (g_hostInfo->positionInBeat>0.749) //sixteenth
    {
        if (g_hostInfo->current16th!=3)
        {
            //DBG("16th3");
            g_hostInfo->broadcast16thHit();
            g_hostInfo->current16th=3;
        }
    }
    else if (g_hostInfo->positionInBeat>0.499)
    {
        if (g_hostInfo->current16th!=2)
        {
            //DBG("16th2");
            g_hostInfo->broadcast16thHit();
            g_hostInfo->current16th=2;
        }
    }
    else if (g_hostInfo->positionInBeat>0.249)
    {
        if (g_hostInfo->current16th!=1)
        {
            //DBG("16th1");
            g_hostInfo->broadcast16thHit();
            g_hostInfo->current16th=1;
        }
    }
    else if (g_hostInfo->positionInBeat>0.0)
    {
        if (g_hostInfo->current16th!=0)
        {
            //DBG("16th0");
            g_hostInfo->broadcast16thHit();
            g_hostInfo->broadcastBeatStartEvent();
            
            g_hostInfo->current16th=0;
            //param->setValueNotifyingHost(.5);
            
        }
    }
    // DBG(pos.ppqPosition);
    // DBG("16th!");
    
    g_hostInfo->previousTempo=lastPosInfo.bpm;
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // I've added this to avoid people getting screaming feedback
    // when they first compile the plugin, but obviously you don't need to
    // this code if your algorithm already fills all the output channels.
    for (int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    // copy input
    for (int channel = 0; channel < getTotalNumInputChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
        
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            input_buffer[i*2+channel] = channelData[i];
        }
    }
    
    if (mInstaceCount == 1)
    {
        libchuck_slave_process(ck, input_buffer, output_buffer, buffer.getNumSamples());
    }
    
    // copy output
    
    
    
    MidiBuffer::Iterator midiIterator(midiMessages); //iterator to loop through our midi buffer that gets passed into the process block
    MidiBuffer tempMidiBuffer; // temporary midi buffer where we do ou "work" and store transposed midi messages
    MidiMessage tempMessage; // temporary midi message to store each midi message from our incoming buffer
    int midiMessagePos; //temporary varirable to store the location of each midi message that we iterate through
    bool doMidiBroadcast = false;
    
    midiInputBuffer.clear();
    
    
    while(midiIterator.getNextEvent(tempMessage, midiMessagePos)){
        
        //if(tempMessage.isNoteOnOrOff()){
        // tempMessage.setNoteNumber(tempMessage.getNoteNumber() + 12); //transpose the message
        // tempMidiBuffer.addEvent(tempMessage, midiMessagePos);
        //}
        
        midiInputBuffer.addEvent(tempMessage, midiMessagePos);
        doMidiBroadcast = true;
        
        const uint8 *midiVals = tempMessage.getRawData();
        int datasize = tempMessage.getRawDataSize();
        //std::cout<<int(midiVals[0])<<" "<<int(midiVals[1])<<" "<<int(midiVals[2])<<std::endl;
    }
    
    if(doMidiBroadcast)
    {
        g_hostInfo->midiOutputBufferPos = 0;
        g_hostInfo->broadcastMidiEvent();
    }
    
    midiMessages = midiOutputBuffer;
    midiOutputBuffer.clear();
    
    
    
    
    
    
    for (int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
        
        for (int i = 0; i < buffer.getNumSamples(); i++)
        {
            if (mInstaceCount == 1) {
                channelData[i] = output_buffer[i*2+channel];
            } else {
                channelData[i] = 0;
            }
        }
    }
}



//==============================================================================
bool ChuckRacksAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ChuckRacksAudioProcessor::createEditor()
{
    return new ChuckRacksAudioProcessorEditor (this);
}

//==============================================================================
void ChuckRacksAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    
    // Create outer XML element
    XmlElement xml("CHUCKPLUGINSETTINGS");
    
    XmlElement* parameterInfoElement = new XmlElement("PARAMETERS");
    for (int i=0; i<parameterListModel->size(); ++i) {
        if (FloatParameter* p = dynamic_cast<FloatParameter*>(getParameters().getUnchecked(i))) {
            parameterInfoElement->setAttribute(p->getName(50), p->getValue());
            std::cout << "storing: " << parameterInfoElement->getAttributeName(i) << " " << parameterInfoElement->getAttributeValue(i) << std::endl;
        }
    }
    
    xml.addChildElement(parameterInfoElement);
    
   /* XmlElement* fileContainerElement = new XmlElement("FILECONTAINERS");
    for (int i=0; i<fileContainerManagerModel->getNumFileContainers(); ++i) {
        FileContainerModel* f = fileContainerManagerModel->fileContainerModelCollection.at(i);
        fileContainerElement->setAttribute(String(i), "yippie");

        //fileContainerElement->setAttribute(String(f->getUniqueFCId()), f->getCodeDocument().getAllContent());
        DBG("writingXML: " << String(fileContainerElement->getAttributeName(i)));
    }
    
    xml.addChildElement(fileContainerElement);
*/
    copyXmlToBinary(xml, destData);

}

void ChuckRacksAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    
    if (xmlState != nullptr) {
        //make sure it's actually our type of xml object
        if (xmlState->hasTagName("CHUCKPLUGINSETTINGS")) {
            
            forEachXmlChildElement (*xmlState, child)
            {
                if (child->hasTagName ("PARAMETERS"))
                {
                    DBG("restoring parameters...") ;
                    for (int i=0; i<child->getNumAttributes(); ++i) {
                        if (FloatParameter* p = dynamic_cast<FloatParameter*>(getParameters().getUnchecked(i))) {
                            
                        p->setValueNotifyingHost(child->getDoubleAttribute(child->getAttributeName(i)));
                        //p->setValueNotifyingHost((float) child->getDoubleAttribute(p->getName(50),p->getValue()));
                        mapNewParam();
                        parameterListModel->at(i) = child->getAttributeName(i);
                        updateParamNames(i, child->getAttributeName(i));
                        std::cout << parameterListModel->at(i) << std::endl;
                        }
                    }
                }
                
                else if (child->hasTagName("FILECONTAINERS"))
                {
                    DBG("restoring filecontainers...") ;
                    for (int i=0; i<child->getNumAttributes(); ++i) {
                        FileContainerModel* f = fileContainerManagerModel->addFileContainer();
                        f->getCodeDocument().insertText(0, child->getStringAttribute(child->getAttributeName(i)));
                        
                    }
                }
            }
        }
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChuckRacksAudioProcessor();
}
