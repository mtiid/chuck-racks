//
//  FileContainerManagerModel.cpp
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "FileContainerManagerModel.h"
FileContainerManagerModel::FileContainerManagerModel(chuck_inst* ck_)
{
    ck=ck_;
}
FileContainerManagerModel::~FileContainerManagerModel()
{

}
void FileContainerManagerModel::addFileContainer()
{
    fileContainerModels.push_back(new FileContainerModel(ck));
}


void FileContainerManagerModel::removeFileContainer(FileContainerModel* whichPointer)
{
    //for (std::vector<FileContainerModel*>::iterator it = fileContainerModels.begin(); it != fileContainerModels.end(); ++it)
    for (int i=0; i<fileContainerModels.size(); i++) {
        if (fileContainerModels[i]==whichPointer) {
            fileContainerModels.erase(fileContainerModels.begin() + i);
            break;
        }
       
        //std::cout << ' ' << *it;
    }
}