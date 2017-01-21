//
//  FileContainerManagerModel.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "FileContainerManagerModel.h"
#include "PluginProcessor.h"

FileContainerManagerModel::FileContainerManagerModel( chuck_inst* ck_, AudioProcessor* p_)
{
    ck = ck_;
    processor = p_;
}

FileContainerManagerModel::~FileContainerManagerModel()
{

}

void FileContainerManagerModel::addFileContainer()
{
    fileContainerModels.push_back( new FileContainerModel(ck, processor) );
}


void FileContainerManagerModel::removeFileContainer( FileContainerModel* whichPointer )
{
    
    for ( int i=0; i<fileContainerModels.size(); i++ )
    {
        if (fileContainerModels[i] == whichPointer) {
            fileContainerModels.erase( fileContainerModels.begin() + i );
            break;
        }
    }
}



void FileContainerManagerModel::addAllShreds()
{
     for ( int i=0; i<fileContainerModels.size(); i++ )
     {
         fileContainerModels.at(i)->addShred();
     }

}

void FileContainerManagerModel::removeAllShreds()
{
    for ( int i=0; i < fileContainerModels.size(); i++ )
    {
        fileContainerModels.at(i)->removeAllShreds();
    }
}

FileContainerModel* FileContainerManagerModel::findFileContainer( int askedUniqueId )
{
    for (int i=0; i<fileContainerModels.size(); i++)
    {
        //fileContainerModels.at(i)->addShred();
        if (fileContainerModels.at(i)->getUniqueFCId() == askedUniqueId )
        {
            return fileContainerModels.at(i);
        }
    }
    
    return nullptr;
}
