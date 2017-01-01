//
//  FileManager.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 3/20/15.
//
//

#include "FileManager.h"


FileManager::FileManager()
{
    fileChooser = new FileChooser("Open Chuck File", File::nonexistent, "*.ck");
}

void FileManager::openBrowser()
{
    if (fileChooser->browseForFileToOpen())
    {
        File chuckFile (fileChooser->getResult());
        fileName = chuckFile.getFileName();
        filePath = chuckFile.getFullPathName();
    }
    
}
