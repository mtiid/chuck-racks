//
//  FileContainerManagerModel.h
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#ifndef __ChuckRacks__FileContainerManagerModel__
#define __ChuckRacks__FileContainerManagerModel__

#include <stdio.h>
#include <map>
#include <memory>
//#include <tr1/memory>
//#include "PluginProcessor.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "FileContainerModel.h"
#include "FileContainerUI.h"

class FileContainerManagerModel
{
public:
    FileContainerManagerModel(chuck_inst* ck_, AudioProcessor* p_);
    ~FileContainerManagerModel();
    chuck_inst* ck;
    //std::vector<FileContainerModel*> fileContainerModels;
    FileContainerModel* addFileContainer();
    void removeFileContainer(FileContainerModel* fc);
    void addAllShreds();
    void removeAllShreds();
    FileContainerModel* findFileContainer(int askedUniqueId);
    
    CodeDocument consoleDocument;
    std::map<int, FileContainerModel*> fileContainerModelCollection;

    AudioProcessor* processor;
    
private:
    
};



#endif /* defined(__ChuckRacks__FileContainerManagerModel__) */

