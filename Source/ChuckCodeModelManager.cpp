//
//  ChuckCodeModelManager.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "ChuckCodeModelManager.h"
#include "PluginProcessor.h"

ChuckCodeModelManager::ChuckCodeModelManager( chuck_inst* ck_, AudioProcessor* p_)
{
    ck = ck_;
    processor = p_;
}

ChuckCodeModelManager::~ChuckCodeModelManager()
{

}

ChuckCodeModel* ChuckCodeModelManager::addFileContainer()
{
    ChuckCodeModel* fc = new ChuckCodeModel(ck, processor);
    chuckCodeModelCollection.insert( std::make_pair(fc->getUniqueFCId(), fc) );
    
    return fc;
}


void ChuckCodeModelManager::removeFileContainer( ChuckCodeModel* fc )
{
    chuckCodeModelCollection.erase( fc->getUniqueFCId() );
    delete fc;
}



void ChuckCodeModelManager::addAllShreds()
{
    for (auto it : chuckCodeModelCollection)
        if (it.second != nullptr)
            it.second->addShred();
}

void ChuckCodeModelManager::removeAllShreds()
{
    for (auto it : chuckCodeModelCollection)
        it.second->removeAllShreds();
}

ChuckCodeModel* ChuckCodeModelManager::findFileContainer( int askedUniqueId )
{
    auto it = chuckCodeModelCollection.find(askedUniqueId);
    if (it != chuckCodeModelCollection.end())
        return it->second;
    else
        return nullptr;
}
