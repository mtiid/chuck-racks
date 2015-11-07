//
//  FileContainerManagerUI.h
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "../JuceLibraryCode/JuceHeader.h"


#ifndef __ChuckPluginTest4__FileContainerManagerUI__
#define __ChuckPluginTest4__FileContainerManagerUI__

#include <stdio.h>
#include "FileContainerManagerModel.h"
#include "MainViewComponent.h"


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
    void changeListenerCallback(ChangeBroadcaster *source);
    
private:
    FileContainerManagerModel* mManagerModel;
    OwnedArray<FileContainerUI> fileContainerUIs;
    
    Viewport scrollableView;
    MainViewComponent mainView;
    
    void updateFileContainerUILayout();
    
};

#endif /* defined(__ChuckPluginTest4__FileContainerManagerUI__) */
