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

    Array<int> shredIds;
    
    void setCanBeEdited( bool shouldEdit ){ canBeEdited = shouldEdit; };
    bool getCanBeEdited(){ return canBeEdited; };
    
    const int getUniqueFCId() { return uniqueFileContainerId; };
    String getFilename(){ return fileName; };
    
    CodeDocument& getCodeDocument();
    
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

    ConsoleComponent* consoleComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChuckCodeModel);

};

#endif /* defined(__ChuckRacks__ChuckCodeModel__) */
