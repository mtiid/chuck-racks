//
//  FileContainerUI.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "FileContainerUI.h"
#include "Defines.h"

FileContainerUI::FileContainerUI(FileContainerModel* fileContainerModel) :
                //filenameComponent("File", File::nonexistent, true, false, false, "*.ck", String::empty,"Choose a ChucK file to open it in the editor"),
                editorWidth(600),
                editorHeight(600)
{
    mFileContainerModel = fileContainerModel;
    mCodeEditorVisible = mFileContainerModel->getCanBeEdited();
}

void FileContainerUI::init(){
    updateSize();
    
    ScopedPointer<XmlElement> expandSVGUp(XmlDocument::parse(BinaryData::collapse_svg));
    ScopedPointer<XmlElement> collapseSVGDown(XmlDocument::parse(BinaryData::expand_svg));
    showHideCodeEditorButton = new DrawableButton("Show/Hide Editor", DrawableButton::ButtonStyle::ImageFitted);
    showHideCodeEditorButton->setClickingTogglesState(true);
    showHideCodeEditorButton->setToggleState(true, dontSendNotification);
    showHideCodeEditorButton->setImages(Drawable::createFromSVG(*expandSVGUp),
                                        nullptr,
                                        Drawable::createFromSVG(*collapseSVGDown),
                                        Drawable::createFromSVG(*expandSVGUp),
                                        Drawable::createFromSVG(*collapseSVGDown),
                                        Drawable::createFromSVG(*collapseSVGDown),
                                        Drawable::createFromSVG(*expandSVGUp),
                                        Drawable::createFromSVG(*collapseSVGDown));
    showHideCodeEditorButton->setColour(DrawableButton::backgroundOnColourId, Colour(0.0f,0.0f,0.0f,0.0f));
    addAndMakeVisible(showHideCodeEditorButton);
    showHideCodeEditorButton->setBounds(2, 5, 20,20);
    showHideCodeEditorButton->addListener(this);
    
    addShredButton = new DrawableButton("Add Shreds", DrawableButton::ButtonStyle::ImageFitted);
    ScopedPointer<XmlElement> addShredSVGUp(XmlDocument::parse(BinaryData::addshrediconUp_svg));
    ScopedPointer<XmlElement> addShredSVGDown(XmlDocument::parse(BinaryData::addshrediconDown_svg));
    
    addShredButton->setImages(Drawable::createFromSVG(*addShredSVGUp), Drawable::createFromSVG(*addShredSVGUp), Drawable::createFromSVG(*addShredSVGDown));
    addAndMakeVisible(addShredButton);
    addShredButton->setBounds(28, 5, 20,20);
    addShredButton->addListener(this);
    
    /*
    removeShredButton = new DrawableButton("Remove All Shreds", DrawableButton::ButtonStyle::ImageFitted);
    ScopedPointer<XmlElement> removeShredSVGUp(XmlDocument::parse(BinaryData::removeAllShredUp_svg));
    ScopedPointer<XmlElement> removeShredSVGDown(XmlDocument::parse(BinaryData::removeAllShredDown_svg));
    removeShredButton->setImages(Drawable::createFromSVG(*removeShredSVGUp), Drawable::createFromSVG(*removeShredSVGUp), Drawable::createFromSVG(*removeShredSVGDown));
    addAndMakeVisible(removeShredButton);
    removeShredButton->setBounds(52, 5, 20, 20);
    removeShredButton->addListener(this);
    */
     
    openFileButton = new TextButton("Open");
    addAndMakeVisible(openFileButton);
    openFileButton->setButtonText("Open");
    openFileButton->setBounds(400, 5, 60,20);
    openFileButton->addListener(this);
    
    saveFileButton = new TextButton("Save");
    addAndMakeVisible(saveFileButton);
    saveFileButton->setButtonText("Save");
    saveFileButton->setBounds(470, 5, 60,20);
    saveFileButton->addListener(this);
    
    
    
    
    
    // Create the editor..
    addChildComponent(codeEditor = new CodeEditorComponent (mFileContainerModel->getCodeDocument(), &ckTokeniser));

    if (codeEditor->getDocument().getAllContent()=="") {
        codeEditor->loadContent(
//        (
                                "//my id:"
                                 + String(mFileContainerModel->getUniqueFCId()) +
                                 "\n"
                                + String(mFileContainerModel->getUniqueFCId()) +
                                " => int myId; \n"
//                                 "/*"
//                                 "\n"
//                                 "   Type in your ChucK code\n"
//                                 "   or load a file\n"
//                                 "\n"
//                                 "*/\n"
//                                 "\n"
//                                 "SqrOsc osc=>dac; \n"
//                                 "1::second=>now; \n"
//                                 );
        /*
        "SqrOsc osc => dac;"
        "\n"
        "while(true) \n"
        "{\n"
            
        "   Std.rand2f(30, 1000)=>osc.freq;\n"
        "   PluginHost.sixteenth()=>now; //synced with daw (press play)\n"
        "}"
         */
                                
        "SqrOsc osc => dac;\n"
        "0.1=> osc.gain;\n"
        "\n"
        "spork ~ updateVolume();\n"
        "while(true)\n"
        "{\n"
        "    Std.rand2(30, 80) => int randomMidiNote;\n"
        "    Std.mtof( randomMidiNote )=> float noteFreq; // mtof == Midi To Frequency\n"
        "    noteFreq => osc.freq;\n"
        "    //PluginPanel.getValue( myId, 0 ) => osc.gain;\n"
        "    repeat ( Std.rand2(1, 3) ) //1,2 or 3 sixteenths\n"
        "    {\n"
        "        PluginHost.sixteenth()=>now; //synced with daw (press play)\n"
        "    }\n"
        "}\n"
        "\n"
        "fun void updateVolume()\n"
        "{\n"
        "    while(true)\n"
        "    {\n"
        "        PluginPanel.getValue( myId, 0 ) => osc.gain; //knob 0 controls volume \n"
        "        10::ms => now;\n"
        "    }\n"
        "}\n"
                                //TODO: Add a default file (from examples ) and load that instead of hardcoding this
        );
    }else {
        codeEditor->loadContent(codeEditor->getDocument().getAllContent());
        //std::cout << "content loaded" << std::endl;
    }
    
    
#ifdef  USE_VER1_KNOBS
    for(int i=0; i<knobAmount; i++)
    {
        knobs.push_back(new Slider("knob"+String(i)));
        addAndMakeVisible(knobs.back());
        
        knobs.back()->setRange(0.0, 1.0);
        knobs.back()->setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
        knobs.back()->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
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
#endif //USE_VER1_KNOBS
    
    switch ( currentViewMode ) {
        case AppViewMode::RackView:
            codeEditor->setBounds( 1, 30, editorWidth-2, editorHeight-31 );
            break;
        case AppViewMode::TabView:
            codeEditor->setBounds( 1, 30, editorWidth-2, editorHeight );
            break;
        default:
            break;
    }

    codeEditor->setVisible( mCodeEditorVisible );
    
    // Create a file chooser control to load files into it..
    //addAndMakeVisible (filenameComponent);
    //filenameComponent.addListener (this);
    
    startTimer( 50 );
}



FileContainerUI::~FileContainerUI()
{
    //filenameComponent.removeListener(this);
}

void FileContainerUI::paint( Graphics& g )
{
    if ( mCodeEditorVisible )
    {
        g.fillAll(Colour(100, 106, 127));
    }else{
        g.fillAll(Colour(50, 53, 64));
    }
    
    g.setColour(Colour(40, 43, 34));
    g.drawRect(getLocalBounds(), 1);
}

void FileContainerUI::updateSize()
{
    switch (currentViewMode)
    {
        case AppViewMode::RackView :
            editorHeight = 410;
            break;
        case AppViewMode::TabView :
            editorHeight = 629;
            break;
        default:
            break;
    }
    
    if (mCodeEditorVisible)
    {
        setSize(editorWidth, editorHeight);
    }else{
        setSize(editorWidth, 30);
    }
}


void FileContainerUI::timerCallback()
{
    //gainKnob->setValue(getProcessor()->getParameter(VolumeKnobAudioProcessor::gainParam), NotificationType::dontSendNotification);
#ifdef USE_VER1_KNOBS
    for( int i=0; i<knobs.size(); i++ )
    {
        knobs.at(i)->setValue(mFileContainerModel->knobInfos.at(i).value01);

    }
    //knobs.at(0)->setValue(mFileContainerModel->testParameter->getValue());
#endif //USE_VER1_KNOBS
}

void FileContainerUI::sliderValueChanged(juce::Slider *slider)
{
    for(int i=0; i<knobs.size(); i++)
    {
    if(slider == knobs.at(i))
        {
        //getProcessor()->setParameter(VolumeKnob6AudioProcessor::gainParam, (float)gainKnob->getValue());
        mFileContainerModel->knobInfos.at(i).value01 = (float)knobs.at(i)->getValue();
         
        std::cout << "Slider " << i << " changed" << std::endl;
        }
    }
    /*
    if (slider == knobs.at(0))
    {
        mFileContainerModel->testParameter->beginChangeGesture();
        mFileContainerModel->testParameter->setValueNotifyingHost(slider->getValue());
        mFileContainerModel->testParameter->endChangeGesture();
    }
     */
}


void FileContainerUI::filenameComponentChanged (FilenameComponent*)
{
    //codeEditor->loadContent (filenameComponent.getCurrentFile().loadFileAsString());
}

void FileContainerUI::buttonClicked(Button *buttonThatWasPressed)
{

    if (buttonThatWasPressed == showHideCodeEditorButton) {
        mCodeEditorVisible = showHideCodeEditorButton->getToggleState();
        codeEditor->setVisible(mCodeEditorVisible);
        mFileContainerModel->setCanBeEdited(mCodeEditorVisible);
        updateSize();
        sendChangeMessage();
    }
    
    else if ( buttonThatWasPressed == addShredButton )
    {
        mFileContainerModel->addShred();
    }
    
    else if (buttonThatWasPressed == removeShredButton )
    {
        mFileContainerModel->removeLastShred();
    }
    
    else if (buttonThatWasPressed == saveFileButton)
    {
        FileChooser fc ("Choose a file to save...",
                        File::getCurrentWorkingDirectory(),
                        "*.ck",
                        true);
        
        if ( fc.browseForFileToSave (true) )
        {
            File chosenFile = fc.getResult();
            
            AlertWindow::showMessageBoxAsync (AlertWindow::InfoIcon,
                                              "File Chooser...",
                                              "You picked: " + chosenFile.getFullPathName());
            fc.getResult().replaceWithText(mFileContainerModel->getCodeDocument().getAllContent());
        }
    }
    
    else if (buttonThatWasPressed == openFileButton)
    {
        FileChooser fc ("Choose a file to open...",
                        File::getCurrentWorkingDirectory(),
                        "*.ck",
                        true);
        
        if( fc.browseForFileToOpen() )
        {
            String chosen;
            fc.getResult();
            chosen = fc.getResult().getFullPathName();
            AlertWindow::showMessageBoxAsync (AlertWindow::InfoIcon,
                                              "File Chooser...",
                                              "You picked: " + chosen);
            codeEditor->loadContent(fc.getResult().loadFileAsString());
            //mFileContainerModel->codeDocument.
        }
    }
}

void FileContainerUI::setViewMode( AppViewMode vm )
{
    currentViewMode = vm;
}



