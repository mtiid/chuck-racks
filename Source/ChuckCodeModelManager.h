//
//  ChuckCodeModelManager.h
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#ifndef __ChuckRacks__ChuckCodeModelManager__
#define __ChuckRacks__ChuckCodeModelManager__

#include <stdio.h>
#include <map>
#include <memory>
#include "../JuceLibraryCode/JuceHeader.h"
#include "ChuckCodeModel.h"
#include "ChuckCodeComponent.h"

class ChuckCodeModelManager
{
public:
    ChuckCodeModelManager(chuck_inst* ck_, AudioProcessor* p_);
    ~ChuckCodeModelManager();
    chuck_inst* ck;
    ChuckCodeModel* addFileContainer();
    void removeFileContainer(ChuckCodeModel* fc);
    void addAllShreds();
    void removeAllShreds();
    int getNumFileContainers(){return chuckCodeModelCollection.size();};
    ChuckCodeModel* findFileContainer(int askedUniqueId);
    
    //CodeDocument consoleDocument;
    std::map<int, ChuckCodeModel*> chuckCodeModelCollection;

    AudioProcessor* processor;
    
private:
  
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChuckCodeModelManager);
};



#endif /* defined(__ChuckRacks__ChuckCodeModelManager__) */

