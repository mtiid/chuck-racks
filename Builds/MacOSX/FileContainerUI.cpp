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
    
    setSize(400, 400);
    
    setOpaque (true);
    
    addAndMakeVisible(addShredButton=new TextButton("Add Shred"));
    addShredButton->setButtonText("Add Shred");
    addShredButton->setBounds(0, 0, 50,50);
    addShredButton->addListener(this);
    
    addAndMakeVisible(removeShredButton=new TextButton("Remove Shred"));
    removeShredButton->setButtonText("Remove Shred");
    removeShredButton->setBounds(120, 0, 50,50 );
    removeShredButton->addListener(this);
    
    // Create the editor..
    addAndMakeVisible (codeEditor = new CodeEditorComponent (m_fileContainerModel->codeDocument, &ckTokeniser));
    codeEditor->setBoundsRelative(0.0, 0.2, 0.8, 0.8);
    
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
    
}

void FileContainerUI::sliderValueChanged(juce::Slider *slider)
{
    
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



