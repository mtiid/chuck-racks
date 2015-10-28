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
    
    //ScrollBar scrollbar;
    
    FileContainerManagerUI(FileContainerManagerModel* managerModel);
    ~FileContainerManagerUI();
    
    void init ();
    void paint(Graphics& g);
    void addNewFileContainerUI();
    void changeListenerCallback(ChangeBroadcaster *source);
    
private:
    FileContainerManagerModel* m_managerModel;
    OwnedArray<FileContainerUI> fileContainerUIs;
    
    Viewport scrollableView;
    MainViewComponent mainView;
    
    void updateFileContainerUILayout();
    
};

#endif /* defined(__ChuckPluginTest4__FileContainerManagerUI__) */
