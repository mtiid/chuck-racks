//
//  FileContainerManagerModel.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "FileContainerManagerModel.h"
#include "PluginProcessor.h"

FileContainerManagerModel::FileContainerManagerModel( chuck_inst* ck_ )
{
    ck = ck_;
}

FileContainerManagerModel::~FileContainerManagerModel()
{

}

void FileContainerManagerModel::addFileContainer()
{
    fileContainerModels.push_back( new FileContainerModel( ck ) );
}


void FileContainerManagerModel::removeFileContainer( FileContainerModel* whichPointer )
{
    //for (std::vector<FileContainerModel*>::iterator it = fileContainerModels.begin(); it != fileContainerModels.end(); ++it)
    for ( int i=0; i<fileContainerModels.size(); i++ )
    {
        if (fileContainerModels[i] == whichPointer) {
            fileContainerModels.erase( fileContainerModels.begin() + i );
            break;
        }
       
        //std::cout << ' ' << *it;
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


AudioProcessor * FileContainerManagerModel::getProcessor()
{
    AudioProcessor * processor = ChuckRacksAudioProcessor::getProcessor();
    return processor;
}
