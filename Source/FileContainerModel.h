//
//  FileContainerModel.h
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#ifndef __ChuckPluginTest4__FileContainerModel__
#define __ChuckPluginTest4__FileContainerModel__

#include <stdio.h>
#include "KnobInfo.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "libchuck.h"
#include "ConsoleGlobal.h"




class FileContainerModel
{
public:
    FileContainerModel(chuck_inst* ck_);
    ~FileContainerModel();
    chuck_inst *ck;

    
    void addShred();
    void removeLastShred();
    void replaceShred();
    void removeAllShreds();
    
    std::vector<int> shredIds;
    std::vector<KnobInfo> knobInfos;
    //std::vector<AudioParameterFloat> knobParameters;
    //std::vector<AudioProcessorParameter*> knobParameters;
    
    AudioProcessorParameter* testParameter;

    
    ScopedPointer<FileChooser> fileChooser;
    String fileName;
    String filePath;
    
    CodeDocument codeDocument;
    void openBrowser();

    String lastFileLoaded;

    void setCanBeEdited(bool shouldEdit){ canBeEdited = shouldEdit;};
    bool getCanBeEdited(){return canBeEdited;};
    
    int uniqueFileContainerId;
    void setProcessorReference( AudioProcessor * processorReference_);
    AudioProcessor * getProcessor();
private:
    bool canBeEdited;
    AudioProcessor * processorReference;


};

#endif /* defined(__ChuckPluginTest4__FileContainerModel__) */
