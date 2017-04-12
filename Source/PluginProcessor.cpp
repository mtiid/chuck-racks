/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic startup code for a Juce application.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "ulib_pluginhost.h"
#include "ulib_PluginParameters.h"

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
)
#endif

{
    checkForMultipleInstances();
    initializeParameterList();
}

ChuckRacksAudioProcessor::~ChuckRacksAudioProcessor()
{
    cleanUp();
    instanceCounter->decrementCount();
}

void ChuckRacksAudioProcessor::checkForMultipleInstances()
{
    instanceCounter->incrementCount();
    thisInstanceCount = instanceCounter->getCount();

    if (isSingleInstance() == false)
    {
        AlertWindow::showMessageBox (AlertWindow::AlertIconType::NoIcon,
                                     "Sorry!",
                                     "Currently only a single instance of ChuckRacks may run at once.\n This will be fixed in a future update.",
                                     "Okay",
                                     nullptr);
        
    }
}

void ChuckRacksAudioProcessor::initializeParameterList()
{
    for (int i=0; i<512; i++)
    {
        NormalisableRange<float> paramRange(0.0, 1.0, 0.1, 1.0);
        String id = String(i+1);
        FloatParameter* param = new FloatParameter(id, id, paramRange, 1.0);
        addParameter(param);
    }
    
    parameterListModel = new std::map<int, String>;
    lastBarStart = -1;
    dynamic_cast<FloatParameter*>(getParameters().getUnchecked(0))->setName("Yes!");
}

void ChuckRacksAudioProcessor::cleanUp()
{
    if (isSingleInstance()) {
        if (ck) {
            libchuck_destroy(ck);
            ck = NULL;
        }
        
        if(input_buffer) { delete[] input_buffer; input_buffer = NULL; }
        if(output_buffer) { delete[] output_buffer; output_buffer = NULL; }
        
        if (chuckCodeModelManager) { delete chuckCodeModelManager; chuckCodeModelManager = NULL; }
    }
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
    cleanUp();
    
    fprintf(stderr, "ChuckRacksAudioProcessor::prepareToPlay\n");
    chuck_options options;
    libchuck_options_reset(&options);
    options.slave = true;
    // hardcode (HACK!)
    options.buffer_size = samplesPerBlock;
    options.adaptive_buffer_size = 0;
    options.num_channels = 2;
    options.sample_rate = sampleRate;
    
    //TODO: check if a valid instance of chuck is running (how do I do this?)
    ck = libchuck_create(&options);
    
    libchuck_add_module(ck, (void*)pluginhost_query);
    libchuck_add_module(ck, (void*)pluginParameters_query);
    libchuck_vm_start(ck);
    
    input_buffer = new float[options.buffer_size*options.num_channels];
    output_buffer = new float[options.buffer_size*options.num_channels];
    
    chuckCodeModelManager = new ChuckCodeModelManager(ck, this);
    
    g_hostInfo->midiInputBufferP = (&midiInputBuffer);
    g_hostInfo->midiOutputBufferP = (&midiOutputBuffer);
    
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
    if (thisInstanceCount == 1) {
        
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
            lastBarStart = -1;
        }
        
        if( pos.timeSigDenominator != g_hostInfo->timeSigDenominator )
        {
            g_hostInfo->timeSigDenominator = pos.timeSigDenominator;
        }
        
        if( pos.timeSigNumerator != g_hostInfo->timeSigNumerator )
        {
            g_hostInfo->timeSigNumerator = pos.timeSigNumerator;
        }
        
        g_hostInfo->wasPlaying = lastPosInfo.isPlaying;
        
        if( pos.isPlaying )
        {
            if ((pos.ppqPositionOfLastBarStart != lastBarStart) && (pos.ppqPosition >= pos.ppqPositionOfLastBarStart))
            {
                g_hostInfo->broadcastNextBarEvent();
                lastBarStart = pos.ppqPositionOfLastBarStart;
            }
        }
        
        g_hostInfo->position = pos.ppqPosition;
        g_hostInfo->positionInBar = pos.ppqPosition - pos.ppqPositionOfLastBarStart;
        g_hostInfo->positionInBeat = fmod( pos.ppqPosition,1 );
        g_hostInfo->lastBarStartPosition = pos.ppqPositionOfLastBarStart;
        //DBG(positionInBeat);
        if (g_hostInfo->positionInBeat>0.749) //sixteenth
        {
            if (g_hostInfo->currentSixteenth!=3)
            {
                //DBG("16th3");
                g_hostInfo->broadcastSixteenthHit();
                g_hostInfo->currentSixteenth=3;
            }
        }
        else if (g_hostInfo->positionInBeat>0.499)
        {
            if (g_hostInfo->currentSixteenth!=2)
            {
                //DBG("16th2");
                g_hostInfo->broadcastEighthHit();
                g_hostInfo->broadcastSixteenthHit();
                g_hostInfo->currentSixteenth=2;
            }
        }
        else if (g_hostInfo->positionInBeat>0.249)
        {
            if (g_hostInfo->currentSixteenth!=1)
            {
                //DBG("16th1");
                g_hostInfo->broadcastSixteenthHit();
                g_hostInfo->currentSixteenth=1;
            }
        }
        else if (g_hostInfo->positionInBeat>0.0)
        {
            if (g_hostInfo->currentSixteenth!=0)
            {
                //DBG("16th0");
                g_hostInfo->broadcastQuarterHit();
                g_hostInfo->broadcastEighthHit();
                g_hostInfo->broadcastSixteenthHit();
                g_hostInfo->currentSixteenth = 0;
                
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
        
        libchuck_slave_process(ck, input_buffer, output_buffer, buffer.getNumSamples());
        
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
                channelData[i] = output_buffer[i*2+channel];
            }
        }
    }
    else {
        
        for (int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
        {
            float* channelData = buffer.getWritePointer (channel);
            
            for (int i = 0; i < buffer.getNumSamples(); i++)
            {
                channelData[i] = 0;
            }
            
        }
    }
}


//==============================================================================
bool ChuckRacksAudioProcessor::hasEditor() const
{
    if (thisInstanceCount == 1)
    {
        return true;
    } else {
        return false;
    }
}

AudioProcessorEditor* ChuckRacksAudioProcessor::createEditor()
{
    return new ChuckRacksAudioProcessorEditor (this);
}

//==============================================================================
void ChuckRacksAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    if (thisInstanceCount == 1)
    {
        XmlElement xml("CHUCKPLUGINSETTINGS");
        
        XmlElement* parameterInfoElement = new XmlElement("PARAMETERS");
        for (int i=0; i<parameterListModel->size(); ++i) {
            if (FloatParameter* p = dynamic_cast<FloatParameter*>(getParameters().getUnchecked(i))) {
                parameterInfoElement->setAttribute(p->getName(50), p->getValue());
                std::cout << "storing: " << parameterInfoElement->getAttributeName(i) << " " << parameterInfoElement->getAttributeValue(i) << std::endl;
            }
        }
        
        xml.addChildElement(parameterInfoElement);
        
        
        // Add FileContainers to XML tree
        XmlElement* fileContainerElement = new XmlElement("FILECONTAINERS");
        
        for (auto itr : chuckCodeModelManager->chuckCodeModelCollection) {
            ChuckCodeModel* f = itr.second;
            if (f != nullptr) {
                fileContainerElement->setAttribute(Identifier(String("C")+String(itr.first)), String(f->getCodeDocument().getAllContent()));
            }
        }
        
        xml.addChildElement(fileContainerElement);
        
        // Binarize and convert XML to output MemoryBlock
        copyXmlToBinary(xml, destData);
    }
}

void ChuckRacksAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    if (thisInstanceCount == 1)
    {
        // Turn Binarzed data back into XML
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
                    
                    // Restore any FileContainers
                    else if (child->hasTagName("FILECONTAINERS"))
                    {
                        DBG("restoring filecontainers...") ;
                        for (int i=0; i<child->getNumAttributes(); ++i) {
                            ChuckCodeModel* f = chuckCodeModelManager->addFileContainer();
                            f->getCodeDocument().replaceAllContent(child->getStringAttribute(child->getAttributeName(i)));
                        }
                    }
                }
            }
        }
    }
}

bool ChuckRacksAudioProcessor::isSingleInstance()
{
    if (thisInstanceCount == 1) {
        return true;
    } else {
        return false;
    }
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChuckRacksAudioProcessor();
}
