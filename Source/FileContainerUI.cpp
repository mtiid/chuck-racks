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
    mFileContainerModel = fileContainerModel;
    mCodeEditorVisible = mFileContainerModel->getCanBeEdited();
}

void FileContainerUI::init(){
    updateSize();

    //setSize(getParentComponent()->getWidth(), getParentComponent()->getHeight()-200);
    addAndMakeVisible(showHideCodeEditorButton=new ToggleButton);
    showHideCodeEditorButton->setBounds(2, 2, 20,20);
    showHideCodeEditorButton->setToggleState(mCodeEditorVisible, NotificationType::dontSendNotification);
    showHideCodeEditorButton->setButtonText("^");
    showHideCodeEditorButton->setColour(TextButton::ColourIds::buttonColourId, Colours::whitesmoke);
    showHideCodeEditorButton->addListener(this);
    
    addAndMakeVisible(addShredButton=new TextButton("Add Shred"));
    addShredButton->setBounds(22, 2, 40,20);
    addShredButton->setButtonText("+ Shred");
    addShredButton->setColour(TextButton::ColourIds::buttonColourId, Colours::whitesmoke);
    addShredButton->addListener(this);
    
    addAndMakeVisible(removeShredButton=new TextButton("Remove Shred"));
    removeShredButton->setBounds(65, 2, 40, 20);
    removeShredButton->setButtonText("- Shred");
    removeShredButton->addListener(this);
    
    // Create the editor..
    addChildComponent(codeEditor = new CodeEditorComponent (mFileContainerModel->codeDocument, &ckTokeniser));

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
    }else {
        codeEditor->loadContent(codeEditor->getDocument().getAllContent());
        std::cout << "content loaded" << std::endl;
    }
    
    
    /*for(int i=0; i<knobAmount; i++)
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
        
    }*/
    
    codeEditor->setBounds(3, 24, 596, 410);
    //codeEditor->setBounds(3, 24, getParentComponent()->getWidth()-4, getParentComponent()->getHeight()-200);
    //codeEditor->setBounds(3, 24, getWidth()-5, getHeight()-25);
    codeEditor->setVisible(mCodeEditorVisible);
    
    // Create a file chooser control to load files into it..
    addAndMakeVisible (filenameComponent);
    filenameComponent.addListener (this);
    
    startTimer(50);
    //timerCallback();
    //updateSize();
}



FileContainerUI::~FileContainerUI()
{
    filenameComponent.removeListener(this);
}

void FileContainerUI::paint (Graphics& g)
{
    if (mCodeEditorVisible) {
        g.fillAll(Colour(108, 122, 137));
    }else{
        g.fillAll(Colour(238, 238, 238));
    }
    
    g.drawRect(getLocalBounds(), 1);
}

void FileContainerUI::updateSize(){
    std::cout << "update size" << std::endl;
    if (mCodeEditorVisible) {
        setSize(600, 410);
        //setSize(getParentComponent()->getWidth(), getParentComponent()->getHeight()-200);
    }else{
        setSize(600, 25);
        //setSize(getParentComponent()->getWidth(), 25);
    }
}

void FileContainerUI::showHideCodeEditor(){
    
}


void FileContainerUI::timerCallback()
{
    //gainKnob->setValue(getProcessor()->getParameter(VolumeKnobAudioProcessor::gainParam), NotificationType::dontSendNotification);
    for(int i=0; i<knobs.size(); i++)
    {
        knobs.at(i)->setValue(mFileContainerModel->knobInfos.at(i).value01);

    }

}

void FileContainerUI::sliderValueChanged(juce::Slider *slider)
{
    for(int i=0; i<knobs.size(); i++)
    {
    if(slider == knobs.at(i))
        {
        //getProcessor()->setParameter(VolumeKnob6AudioProcessor::gainParam, (float)gainKnob->getValue());
        mFileContainerModel->knobInfos.at(i).value01=(float)knobs.at(i)->getValue();
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

    if (buttonThatWasPressed == showHideCodeEditorButton) {
        mCodeEditorVisible = showHideCodeEditorButton->getToggleState();
        codeEditor->setVisible(mCodeEditorVisible);
        mFileContainerModel->setCanBeEdited(mCodeEditorVisible);
        std::cout << "Code Editor: " << mCodeEditorVisible << std::endl;
        updateSize();
        sendChangeMessage();
    }
    
    else if (buttonThatWasPressed==addShredButton)
    {
        mFileContainerModel->addShred();
    }
    
    else if (buttonThatWasPressed==removeShredButton)
    {
        mFileContainerModel->removeLastShred();
    }
    
    /*if (buttonThatWasPressed==browseCodeButton) {
        getProcessor()->fileManager.openBrowser();
        lastFileLoaded=getProcessor()->fileManager.fileName;
    }*/
}



