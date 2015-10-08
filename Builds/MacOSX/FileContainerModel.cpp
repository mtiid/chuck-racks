//
//  FileContainerModel.cpp
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "FileContainerModel.h"

FileContainerModel::FileContainerModel(chuck_inst* ck_)
{
    ck = ck_;
    fileChooser = new FileChooser("Open Chuck File", File::nonexistent, "*.ck");
    for (int i=0; i<8; i++)
    {
        knobInfos.push_back(*new KnobInfo());
    }
    
}

void FileContainerModel::addShred()
{
    chuck_result result=libchuck_add_shred(ck, filePath.toRawUTF8(), codeDocument.getAllContent().toRawUTF8());
    //libchuck_add_shred(ck, fileChooser->getFullPathName().toRawUTF8(),
                       //codeEditorDemo->codeDocument.getAllContent().toRawUTF8());
    if(result.type == chuck_result::OK)
    {
        shredIds.push_back(result.shred_id);
        std::cout<<"shred with Id added "<<shredIds.back();
    }
}
void FileContainerModel::removeLastShred()
{
    if(shredIds.size()>0)
    {
    libchuck_remove_shred(ck, shredIds.back());
    std::cout<<"shred with Id removed "<<shredIds.back();
    shredIds.pop_back();
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



