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

FileContainerModel* FileContainerManagerModel::addFileContainer()
{
    FileContainerModel* fc = new FileContainerModel(ck, processor);
    fileContainerModelCollection.insert( std::make_pair(fc->getUniqueFCId(), fc) );
    return fc;
    //fileContainerModels.push_back( new FileContainerModel(ck, processor) );
}


void FileContainerManagerModel::removeFileContainer( FileContainerModel* fc )
{
    fileContainerModelCollection.erase( fc->getUniqueFCId() );
    delete fc;
    /*for ( int i=0; i<fileContainerModels.size(); i++ )
    {
        if (fileContainerModels[i] == whichPointer) {
            fileContainerModels.erase( fileContainerModels.begin() + i );
            break;
        }
    }*/
}



void FileContainerManagerModel::addAllShreds()
{
    for (auto it : fileContainerModelCollection)
        it.second->addShred();
    /*for ( int i=0; i<fileContainerModels.size(); i++ )
     {
         fileContainerModels.at(i)->addShred();
     }*/

}

void FileContainerManagerModel::removeAllShreds()
{
    for (auto it : fileContainerModelCollection)
        it.second->removeAllShreds();
    /*for ( int i=0; i < fileContainerModels.size(); i++ )
    {
        fileContainerModels.at(i)->removeAllShreds();
    }*/
}

FileContainerModel* FileContainerManagerModel::findFileContainer( int askedUniqueId )
{
    return fileContainerModelCollection.find(askedUniqueId)->second;
    /*for (int i=0; i<fileContainerModels.size(); i++)
    {
        //fileContainerModels.at(i)->addShred();
        if (fileContainerModels.at(i)->getUniqueFCId() == askedUniqueId )
        {
            return fileContainerModels.at(i);
        }
    }
    
    return nullptr;*/
}
