//
//  ChuckCodeComponent.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "ChuckCodeComponent.h"
#include "Defines.h"

ChuckCodeComponent::ChuckCodeComponent(ChuckCodeModel* chuckCodeModel)
{
    mChuckCodeModel = chuckCodeModel;
    
    addShredButton = new DrawableButton("Add Shreds", DrawableButton::ButtonStyle::ImageFitted);
    ScopedPointer<XmlElement> addShredSVGUp(XmlDocument::parse(BinaryData::addshrediconUp_svg));
    ScopedPointer<XmlElement> addShredSVGDown(XmlDocument::parse(BinaryData::addshrediconDown_svg));
    
    addShredButton->setImages(Drawable::createFromSVG(*addShredSVGUp), Drawable::createFromSVG(*addShredSVGUp), Drawable::createFromSVG(*addShredSVGDown));
    addAndMakeVisible(addShredButton);
    addShredButton->addListener(this);
    
    
    /*removeShredButton = new DrawableButton("Remove All Shreds", DrawableButton::ButtonStyle::ImageFitted);
     ScopedPointer<XmlElement> removeShredSVGUp(XmlDocument::parse(BinaryData::removeAllShredUp_svg));
     ScopedPointer<XmlElement> removeShredSVGDown(XmlDocument::parse(BinaryData::removeAllShredDown_svg));
     removeShredButton->setImages(Drawable::createFromSVG(*removeShredSVGUp), Drawable::createFromSVG(*removeShredSVGUp), Drawable::createFromSVG(*removeShredSVGDown));
     addAndMakeVisible(removeShredButton);
     removeShredButton->setBounds(52, 5, 20, 20);
     removeShredButton->addListener(this);
     */
    
    saveFileButton = new TextButton("Save");
    addAndMakeVisible(saveFileButton);
    saveFileButton->setButtonText("Save");
    saveFileButton->addListener(this);
    
    openFileButton = new TextButton("Load");
    addAndMakeVisible(openFileButton);
    openFileButton->setButtonText("Load");
    openFileButton->addListener(this);
    
    // Create the editor..
    addAndMakeVisible(codeEditor = new CodeEditorComponent (mChuckCodeModel->getCodeDocument(),
                                                            &ckTokeniser));
    
    codeEditor->setFont(Font(Font::getDefaultMonospacedFontName(), 14.0, 0));
    
    if (codeEditor->getDocument().getAllContent().isEmpty()) {
        codeEditor->loadContent(
                                //        (
                                // "//my id:"
                                // + String(mChuckCodeModel->getUniqueFCId()) +
                                // "\n"
                                // + String(mChuckCodeModel->getUniqueFCId()) +
                                // " => int myId; \n"
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
                                 "   PluginHost.nextSixteenth()=>now; //synced with daw (press play)\n"
                                 "}"
                                 */
                                
                                "SqrOsc osc => dac;\n"
                                "0.1=> osc.gain;\n"
                                "\n"
                                //"spork ~ updateVolume();\n"
                                "while(true)\n"
                                "{\n"
                                "    Std.rand2(30, 80) => int randomMidiNote;\n"
                                "    Std.mtof( randomMidiNote )=> float noteFreq; // mtof == Midi To Frequency\n"
                                "    noteFreq => osc.freq;\n"
                                //"    //PluginPanel.getValue( myId, 0 ) => osc.gain;\n"
                                "    repeat ( Std.rand2(1, 3) ) //1,2 or 3 sixteenths\n"
                                "    {\n"
                                "        PluginHost.nextSixteenth()=>now; //synced with daw (press play)\n"
                                "    }\n"
                                "}\n"
                                "\n"
                                //"fun void updateVolume()\n"
                                //"{\n"
                                //"    while(true)\n"
                                //"    {\n"
                                //"        PluginPanel.getValue( myId, 0 ) => osc.gain; //knob 0 controls volume \n"
                                //"        10::ms => now;\n"
                                //"    }\n"
                                //"}\n"
                                //TODO: Add a default file (from examples ) and load that instead of hardcoding this
                                );
    }else {
        codeEditor->loadContent(mChuckCodeModel->getCodeDocument().getAllContent());
        //std::cout << "content loaded" << std::endl;
    }    
}

ChuckCodeComponent::~ChuckCodeComponent()
{
}

void ChuckCodeComponent::paint( Graphics& g )
{
    g.fillAll(Colour(100, 106, 127));
}

void ChuckCodeComponent::resized(){
    addShredButton->setBounds(5, 5, 20,20);
    saveFileButton->setBounds(getWidth()-59, 5, 56,20);
    openFileButton->setBounds(saveFileButton->getX()-58, 5, 56,20);
    codeEditor->setBounds( 1, 30, getWidth()-4, getHeight()-30 );
}




void ChuckCodeComponent::filenameComponentChanged (FilenameComponent*)
{
    //codeEditor->loadContent (filenameComponent.getCurrentFile().loadFileAsString());
}

void ChuckCodeComponent::buttonClicked(Button *buttonThatWasPressed)
{
    
    if ( buttonThatWasPressed == addShredButton )
    {
        mChuckCodeModel->addShred();
    }
    
    else if (buttonThatWasPressed == removeShredButton )
    {
        mChuckCodeModel->removeLastShred();
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
            fc.getResult().replaceWithText(mChuckCodeModel->getCodeDocument().getAllContent());
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
        }
    }
}

