//
//  FileContainerManagerUI.h
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "../JuceLibraryCode/JuceHeader.h"


#ifndef __ChuckRacks__FileContainerManagerUI__
#define __ChuckRacks__FileContainerManagerUI__

#include <stdio.h>
#include "FileContainerManagerModel.h"
#include "MainViewComponent.h"
#include "AppViewMode.h"

class FileContainerManagerUI :  public Component,
                                public ChangeListener
{
public:
    
    FileContainerManagerUI(FileContainerManagerModel* managerModel);
    ~FileContainerManagerUI();
    
    void paint(Graphics& g) override;
    void resized() override;
    
    void init();
    void addNewFileContainerUI(FileContainerModel* fileContainerModel);
    void changeListenerCallback(ChangeBroadcaster *source) override;
    
    
private:
    FileContainerManagerModel* mManagerModel;
    OwnedArray<FileContainerUI> fileContainerUIs;
    
    ScopedPointer<TextEditor> console;
    
    Viewport scrollableView;
    MainViewComponent mainView;
    TabbedComponent tabView;
    
    void updateFileContainerUILayout();
    
    AppViewMode currentViewMode;
    
    CPlusPlusCodeTokeniser cppTokeniser;
    
    int consoleHeight;

    
};

#endif /* defined(__ChuckRacks__FileContainerManagerUI__) */
