//
//  FilenameComponentExtraExtra.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/25/15.
//
//

#include "FilenameComponentExtra.h"
FilenameComponentExtra::FilenameComponentExtra (const String& name,
                                      const File& currentFile,
                                      const bool canEditFilename,
                                      const bool isDirectory,
                                      const bool isForSaving,
                                      const String& fileBrowserWildcard,
                                      const String& suffix,
                                      const String& textWhenNothingSelected)
: Component (name),
maxRecentFiles (30),
isDir (isDirectory),
isSaving (isForSaving),
isFileDragOver (false),
wildcard (fileBrowserWildcard),
enforcedSuffix (suffix)
{
    addAndMakeVisible (filenameBox);
    filenameBox.setEditableText (canEditFilename);
    filenameBox.addListener (this);
    filenameBox.setTextWhenNothingSelected (textWhenNothingSelected);
    filenameBox.setTextWhenNoChoicesAvailable (TRANS ("(no recently selected files)"));
    
    setBrowseButtonText ("Open");
    
    setCurrentFile (currentFile, true, dontSendNotification);
}

FilenameComponentExtra::~FilenameComponentExtra()
{
}

//==============================================================================
void FilenameComponentExtra::paintOverChildren (Graphics& g)
{
    if (isFileDragOver)
    {
        g.setColour (Colours::red.withAlpha (0.2f));
        g.drawRect (getLocalBounds(), 3);
    }
}

void FilenameComponentExtra::resized()
{
    //getLookAndFeel().layoutFilenameComponent(*this, &filenameBox, browseOpenButton);
}

KeyboardFocusTraverser* FilenameComponentExtra::createFocusTraverser()
{
    // This prevents the sub-components from grabbing focus if the
    // FilenameComponentExtra has been set to refuse focus.
    return getWantsKeyboardFocus() ? Component::createFocusTraverser() : nullptr;
}

void FilenameComponentExtra::setBrowseButtonText (const String& newBrowseButtonText)
{
    browseButtonText = newBrowseButtonText;
    lookAndFeelChanged();
}

void FilenameComponentExtra::lookAndFeelChanged()
{
    //browseButton = nullptr;
    
    //addAndMakeVisible (browseButton = getLookAndFeel().createFilenameComponentExtraBrowseButton (browseButtonText));
    //browseButton->setConnectedEdges (Button::ConnectedOnLeft);
    //resized();
    
    //browseButton->addListener (this);
}

void FilenameComponentExtra::setTooltip (const String& newTooltip)
{
    SettableTooltipClient::setTooltip (newTooltip);
    filenameBox.setTooltip (newTooltip);
}

void FilenameComponentExtra::setDefaultBrowseTarget (const File& newDefaultDirectory)
{
    defaultBrowseFile = newDefaultDirectory;
}

File FilenameComponentExtra::getLocationToBrowse()
{
    return getCurrentFile() == File::nonexistent ? defaultBrowseFile
    : getCurrentFile();
}

void FilenameComponentExtra::buttonClicked (Button*)
{
#if JUCE_MODAL_LOOPS_PERMITTED
    FileChooser fc (isDir ? TRANS ("Choose a new directory")
                    : TRANS ("Choose a new file"),
                    getLocationToBrowse(),
                    wildcard);
    
    if (isDir ? fc.browseForDirectory()
        : (isSaving ? fc.browseForFileToSave (false)
           : fc.browseForFileToOpen()))
    {
        setCurrentFile (fc.getResult(), true);
    }
#else
    jassertfalse; // needs rewriting to deal with non-modal environments
#endif
}

void FilenameComponentExtra::comboBoxChanged (ComboBox*)
{
    setCurrentFile (getCurrentFile(), true);
}

bool FilenameComponentExtra::isInterestedInFileDrag (const StringArray&)
{
    return true;
}

void FilenameComponentExtra::filesDropped (const StringArray& filenames, int, int)
{
    isFileDragOver = false;
    repaint();
    
    const File f (filenames[0]);
    
    if (f.exists() && (f.isDirectory() == isDir))
        setCurrentFile (f, true);
}

void FilenameComponentExtra::fileDragEnter (const StringArray&, int, int)
{
    isFileDragOver = true;
    repaint();
}

void FilenameComponentExtra::fileDragExit (const StringArray&)
{
    isFileDragOver = false;
    repaint();
}

//==============================================================================
String FilenameComponentExtra::getCurrentFileText() const
{
    return filenameBox.getText();
}

File FilenameComponentExtra::getCurrentFile() const
{
    File f (File::getCurrentWorkingDirectory().getChildFile (getCurrentFileText()));
    
    if (enforcedSuffix.isNotEmpty())
        f = f.withFileExtension (enforcedSuffix);
    
    return f;
}

void FilenameComponentExtra::setCurrentFile (File newFile,
                                        const bool addToRecentlyUsedList,
                                        NotificationType notification)
{
    if (enforcedSuffix.isNotEmpty())
        newFile = newFile.withFileExtension (enforcedSuffix);
    
    if (newFile.getFullPathName() != lastFilename)
    {
        lastFilename = newFile.getFullPathName();
        
        if (addToRecentlyUsedList)
            addRecentlyUsedFile (newFile);
        
        filenameBox.setText (lastFilename, dontSendNotification);
        
        if (notification != dontSendNotification)
        {
            triggerAsyncUpdate();
            
            if (notification == sendNotificationSync)
                handleUpdateNowIfNeeded();
        }
    }
}

void FilenameComponentExtra::setFilenameIsEditable (const bool shouldBeEditable)
{
    filenameBox.setEditableText (shouldBeEditable);
}

StringArray FilenameComponentExtra::getRecentlyUsedFilenames() const
{
    StringArray names;
    
    for (int i = 0; i < filenameBox.getNumItems(); ++i)
        names.add (filenameBox.getItemText (i));
    
    return names;
}

void FilenameComponentExtra::setRecentlyUsedFilenames (const StringArray& filenames)
{
    if (filenames != getRecentlyUsedFilenames())
    {
        filenameBox.clear();
        
        for (int i = 0; i < jmin (filenames.size(), maxRecentFiles); ++i)
            filenameBox.addItem (filenames[i], i + 1);
    }
}

void FilenameComponentExtra::setMaxNumberOfRecentFiles (const int newMaximum)
{
    maxRecentFiles = jmax (1, newMaximum);
    
    setRecentlyUsedFilenames (getRecentlyUsedFilenames());
}

void FilenameComponentExtra::addRecentlyUsedFile (const File& file)
{
    StringArray files (getRecentlyUsedFilenames());
    
    if (file.getFullPathName().isNotEmpty())
    {
        files.removeString (file.getFullPathName(), true);
        files.insert (0, file.getFullPathName());
        
        setRecentlyUsedFilenames (files);
    }
}

//==============================================================================
void FilenameComponentExtra::addListener (FilenameComponentListener* const listener)
{
    listeners.add (listener);
}

void FilenameComponentExtra::removeListener (FilenameComponentListener* const listener)
{
    listeners.remove (listener);
}

void FilenameComponentExtra::handleAsyncUpdate()
{
    //Component::BailOutChecker checker (this);
    //listeners.callChecked (checker, &FilenameComponentListener::FilenameComponentChanged, this);
}
