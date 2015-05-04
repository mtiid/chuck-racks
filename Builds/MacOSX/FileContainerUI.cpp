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
    
    // Create the editor..
    addAndMakeVisible (codeEditor = new CodeEditorComponent (m_fileContainerModel->codeDocument, &ckTokeniser));
    
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


void FileContainerUI::timerCallback()
{
    
}

void FileContainerUI::sliderValueChanged(juce::Slider *slider)
{
    
}

void FileContainerUI::buttonClicked(Button* buttonThatWasPressed)
{
    
}

void FileContainerUI::filenameComponentChanged (FilenameComponent*)
{
    codeEditor->loadContent (filenameComponent.getCurrentFile().loadFileAsString());
}
