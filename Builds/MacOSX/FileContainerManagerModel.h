//
//  FileContainerManagerModel.h
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#ifndef __ChuckPluginTest4__FileContainerManagerModel__
#define __ChuckPluginTest4__FileContainerManagerModel__

#include <stdio.h>

#include "../JuceLibraryCode/JuceHeader.h"
#include "FileContainerModel.h"
#include "FileContainerUI.h"


class FileContainerManagerModel
{
public:
    FileContainerManagerModel(chuck_inst* ck_);
    ~FileContainerManagerModel();
    chuck_inst* ck;
    std::vector<FileContainerModel*> fileContainerModels;
    void addFileContainer();
    void removeFileContainer(FileContainerModel* whichPointer);
    void addAllShreds();
    
};



#endif /* defined(__ChuckPluginTest4__FileContainerManagerModel__) */

