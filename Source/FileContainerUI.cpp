//
//  FileContainerUI.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "FileContainerUI.h"
#include "Defines.h"

FileContainerUI::FileContainerUI(FileContainerModel* fileContainerModel)
{
    mFileContainerModel = fileContainerModel;
    
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
    addAndMakeVisible(codeEditor = new CodeEditorComponent (mFileContainerModel->getCodeDocument(),
                                                            &ckTokeniser));
    
    codeEditor->setFont(Font(Font::getDefaultMonospacedFontName(), 14.0, 0));
    
    if (codeEditor->getDocument().getAllContent().isEmpty()) {
        codeEditor->loadContent(
                                //        (
                                // "//my id:"
                                // + String(mFileContainerModel->getUniqueFCId()) +
                                // "\n"
                                // + String(mFileContainerModel->getUniqueFCId()) +
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
                                 "   PluginHost.sixteenth()=>now; //synced with daw (press play)\n"
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
                                "        PluginHost.sixteenth()=>now; //synced with daw (press play)\n"
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
        codeEditor->loadContent(mFileContainerModel->getCodeDocument().getAllContent());
        //std::cout << "content loaded" << std::endl;
    }    
}

FileContainerUI::~FileContainerUI()
{
}

void FileContainerUI::paint( Graphics& g )
{
    g.fillAll(Colour(100, 106, 127));
    g.setColour(Colour(40, 43, 34));
    g.drawRect(getLocalBounds(), 1);
}

void FileContainerUI::resized(){
    addShredButton->setBounds(28, 5, 20,20);
    saveFileButton->setBounds(getWidth()-59, 5, 56,20);
    openFileButton->setBounds(saveFileButton->getX()-58, 5, 56,20);
    codeEditor->setBounds( 1, 30, getWidth()-4, getHeight()-30 );
}




void FileContainerUI::filenameComponentChanged (FilenameComponent*)
{
    //codeEditor->loadContent (filenameComponent.getCurrentFile().loadFileAsString());
}

void FileContainerUI::buttonClicked(Button *buttonThatWasPressed)
{
    
    if ( buttonThatWasPressed == addShredButton )
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

