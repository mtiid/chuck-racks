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
    void removeAllShreds();
    FileContainerModel* findFileContainer(int askedUniqueId);
    void setProcessorReference( AudioProcessor * processorReference_);
    AudioProcessor * getProcessor();
    CodeDocument consoleDocument;
private:
    AudioProcessor * processorReference;
};



#endif /* defined(__ChuckRacks__FileContainerManagerModel__) */

