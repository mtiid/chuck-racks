//
//  ChuckCodeModel.h
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#ifndef __ChuckRacks__ChuckCodeModel__
#define __ChuckRacks__ChuckCodeModel__

#include <stdio.h>
#include "KnobInfo.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include "libchuck.h"
#include "ConsoleComponent.h"

class ChuckCodeModel
{
public:
    ChuckCodeModel( chuck_inst* ck_, AudioProcessor* p_ );
    ~ChuckCodeModel();

    
    void addShred();
    void removeLastShred();
    void removeShred(int idNumber);
    void replaceShred();
    void removeAllShreds();
    void openBrowser();

    std::vector<int> shredIds;
    
    void setCanBeEdited( bool shouldEdit ){ canBeEdited = shouldEdit; };
    bool getCanBeEdited(){ return canBeEdited; };
    
    const int getUniqueFCId() { return uniqueFileContainerId; };
    
    CodeDocument& getCodeDocument();
    
    void addListener(ConsoleComponent* listenerToAdd);
    void removeListener(ConsoleComponent* listenerToRemove);
    
private:
    
    chuck_inst *ck;
    AudioProcessor* processor;
    
    bool canBeEdited;
    String lastFileLoaded;
    
    ScopedPointer<FileChooser> fileChooser;
    String fileName;
    String filePath;
    
    CodeDocument codeDocument;
    
    int uniqueFileContainerId;

    ListenerList<ConsoleComponent> listeners;

};

#endif /* defined(__ChuckRacks__ChuckCodeModel__) */
