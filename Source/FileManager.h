//
//  FileManager.h
//  ChuckRacks
//
//  Created by Rodrigo Sena on 3/20/15.
//
//

#ifndef __ChuckRacks__FileManager__
#define __ChuckRacks__FileManager__

#include "../JuceLibraryCode/JuceHeader.h"

#endif /* defined(__ChuckRacks__FileManager__) */

class FileManager
{
public:
    FileManager();
    
    FileChooser* fileChooser;
    String fileName;
    String filePath;
    
    CodeDocument codeDocument;
    void openBrowser();
    
    
};
