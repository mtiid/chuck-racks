//
//  FileContainerUI.cpp
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "FileContainerUI.h"

FileContainerUI::FileContainerUI(FileContainerModel* fileContainerModel) : filenameComponent("File", File::nonexistent, true, false, false, "*.ck", String::empty,"Choose a ChucK file to open it in the editor")
{
    m_fileContainerModel=fileContainerModel;
}

void FileContainerUI::init(){
    setOpaque (true);
    
    addAndMakeVisible(addShredButton=new TextButton("Add Shred"));
    addShredButton->setButtonText("Add Shred");
    addShredButton->setBoundsRelative(0, 0, .1,.1);
    addShredButton->addListener(this);
    
    addAndMakeVisible(removeShredButton=new TextButton("Remove Shred"));
    removeShredButton->setButtonText("Remove Shred");
    removeShredButton->setBoundsRelative(.2, 0, .1,.1 );
    removeShredButton->addListener(this);
    
    // Create the editor..
    addAndMakeVisible (codeEditor = new CodeEditorComponent (m_fileContainerModel->codeDocument, &ckTokeniser));
    codeEditor->setBoundsRelative(0.0, 0.2, 1.0, 0.8);
    
    if (codeEditor->getDocument().getAllContent()=="") {
        codeEditor->loadContent ("\n"
                                 "/*"
                                 "\n"
                                 "   Type in your ChucK code\n"
                                 "   or load a file\n"
                                 "\n"
                                 "*/\n"
                                 "\n"
                                 "SqrOsc osc=>dac; \n"
                                 "1::second=>now; \n"
                                 );
    }
    else
    {
        codeEditor->loadContent(codeEditor->getDocument().getAllContent());
    }
    
    
    
    for(int i=0; i<knobAmount; i++)
    {
        knobs.push_back(new Slider("knob"+String(i)));
        addAndMakeVisible(knobs.back());
        
        knobs.back()->setRange(0.0, 1.0);
        knobs.back()->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        knobs.back()->setColour(Slider::rotarySliderFillColourId, Colours::black);
        knobs.back()->setColour(Slider::rotarySliderOutlineColourId, Colours::black);
        knobs.back()->addListener(this);
        if(i<knobsPerRow)
        {
            std::cout<<"row 1 "<<i<<std::endl;
            knobs.back()->setBounds(knobStartX+(i*(knobSpacing+knobSize)), knobStartY, knobSize, knobSize);
        }
        else
        {
            std::cout<<"row 2"<<i<<std::endl;
            knobs.back()->setBounds(knobStartX+((i-knobsPerRow)*(knobSpacing+knobSize)), knobStartY+(knobSpacing+knobSize), knobSize, knobSize);
        }
        
    }
    
    
    
    
    
    // Create a file chooser control to load files into it..
    addAndMakeVisible (filenameComponent);
    filenameComponent.addListener (this);
    
    
    startTimer(50);
    timerCallback();
}



FileContainerUI::~FileContainerUI()
{
    filenameComponent.removeListener(this);
}

void FileContainerUI::paint (Graphics& g)
{
    g.fillAll(Colours::blue);
}


void FileContainerUI::timerCallback()
{
    //gainKnob->setValue(getProcessor()->getParameter(VolumeKnobAudioProcessor::gainParam), NotificationType::dontSendNotification);
    for(int i=0; i<knobs.size(); i++)
    {
        knobs.at(i)->setValue(m_fileContainerModel->knobInfos.at(i).value01);

    }

}

void FileContainerUI::sliderValueChanged(juce::Slider *slider)
{
    for(int i=0; i<knobs.size(); i++)
    {
    if(slider == knobs.at(i))
        {
        //getProcessor()->setParameter(VolumeKnob6AudioProcessor::gainParam, (float)gainKnob->getValue());
        m_fileContainerModel->knobInfos.at(i).value01=(float)knobs.at(i)->getValue();
        std::cout<<"Slider "<<i<<" changed" << std::endl;
        }
    }
}


void FileContainerUI::filenameComponentChanged (FilenameComponent*)
{
    codeEditor->loadContent (filenameComponent.getCurrentFile().loadFileAsString());
}

void FileContainerUI::buttonClicked(Button *buttonThatWasPressed)
{
    if (buttonThatWasPressed==addShredButton)
    {
        m_fileContainerModel->addShred();
    }
    
    if (buttonThatWasPressed==removeShredButton)
    {
        m_fileContainerModel->removeLastShred();
    }
    

    
    
    
    //if (buttonThatWasPressed==browseCodeButton) {
    //    getProcessor()->fileManager.openBrowser();
    //    lastFileLoaded=getProcessor()->fileManager.fileName;
    //}
}



