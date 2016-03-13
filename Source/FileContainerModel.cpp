//
//  FileContainerModel.cpp
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "FileContainerModel.h"
#include <sstream>

FileContainerModel::FileContainerModel(chuck_inst* ck_) : canBeEdited(true)
{
    ck = ck_;
    
    ScopedPointer<Random> random = new Random();
    uniqueFileContainerId = random->nextInt();
    
    std::stringstream ss;
    ss << uniqueFileContainerId;
    std::string uniqueFileContainerIdAsString = ss.str();
    
    fileChooser = new FileChooser("Open Chuck File", File::nonexistent, "*.ck");
    for (int i=0; i<8; i++)
    {
        knobInfos.push_back(*new KnobInfo());
        //String name = String
        //knobParameters.push_back(new AudioParameterFloat(S, );
        
        NormalisableRange<float> gainRange(0.0, 1.0, 0.1, 1.0);
        //knobParameters.push_back(new AudioParameterFloat("gainParam", "Gain", gainRange, 1.0));
        //knobParameters.push_back(*new AudioParameterFloat(String(random->nextInt()),String(random->nextInt()), gainRange, 1.0));

        //getProcessor()->addParameter (knobParameters.back());
    }
   
    NormalisableRange<float> gainRange(0.0, 1.0, 0.1, 1.0);
    testParameter = new AudioParameterFloat("gainParam", "Gain", gainRange, 1.0);
    
    //getProcessor() -> getInputChannelName(0);
    //getProcessor() -> addParameter(testParameter);
    //if(getProcessor() != NULL)
    //    getProcessor() -> addParameter(testParameter);
    //else
     //   DBG("getProcessor inside FileContainerModel was null");

    
    
}

void FileContainerModel::addShred()
{
    chuck_result result = libchuck_add_shred(ck, filePath.toRawUTF8(), codeDocument.getAllContent().toRawUTF8());
    //libchuck_add_shred(ck, fileChooser->getFullPathName().toRawUTF8(),
    //codeEditorDemo->codeDocument.getAllContent().toRawUTF8());
    if(result.type == chuck_result::OK)
    {
        shredIds.push_back(result.shred_id);
        std::cout<<"shred with Id added "<<shredIds.back()<< "\n";
    }
    else
    {
        std::string resStr(libchuck_last_error_string(ck));
        std::cout<<"problem add shred:" + resStr << "\n";
        ConsoleGlobal::Instance()->addText(resStr);
        //CONSOLE ADD TEXT
        
    }
}
void FileContainerModel::removeLastShred()
{
    if(shredIds.size()>0)
    {
        chuck_result result = libchuck_remove_shred(ck, shredIds.back());
        if(result.type == chuck_result::OK)
        {
            std::cout<<"shred with Id removed "<<shredIds.back() << "\n";
            shredIds.pop_back();
        }
        else
        {
            std::string resStr(libchuck_last_error_string(ck));
            std::cout<<"problem removing shred:" + resStr << "\n";
            ConsoleGlobal::Instance()->addText(resStr);
            ///getProcessor()->fileContainerManagerModel->addTextToConsole(resStr);
            //CONSOLE ADD TEXT
        }
        
    }
    
}


void FileContainerModel::replaceShred()
{
    chuck_result result=libchuck_replace_shred(ck, shredIds.back(), filePath.toRawUTF8(),
                                               codeDocument.getAllContent().toRawUTF8());
    if(result.type == chuck_result::OK)
    {
        shredIds.pop_back();
        shredIds.push_back(result.shred_id);
    }
    
}
void FileContainerModel::removeAllShreds()
{
    
    while (!shredIds.empty())
    {
        removeLastShred();
    }
}

void FileContainerModel::openBrowser()
{
    if (fileChooser->browseForFileToOpen())
    {
        File chuckFile (fileChooser->getResult());
        fileName = chuckFile.getFileName();
        filePath = chuckFile.getFullPathName();
    }
    
}

void FileContainerModel::setProcessorReference( AudioProcessor * processorReference_)
{
    processorReference = processorReference_;
}
AudioProcessor * FileContainerModel::getProcessor()
{
    DBG("entered getProcessor in fileContainerModel");
    if(processorReference != NULL)
    {
        return processorReference;
    }
    else
    {
        DBG("trying to access processor reference not set in filecontainer!!");
        return NULL;
    }
    
}


