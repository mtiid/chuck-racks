//
//  FileManager.h
//  ChuckPluginTest4
//
//  Created by Rodrigo Sena on 3/20/15.
//
//

#ifndef __ChuckPluginTest4__FileManager__
#define __ChuckPluginTest4__FileManager__

#include "../JuceLibraryCode/JuceHeader.h"

#endif /* defined(__ChuckPluginTest4__FileManager__) */

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