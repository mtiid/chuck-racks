//
//  FileContainerModel.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "FileContainerModel.h"
#include "PluginProcessor.h"
#include <sstream>

FileContainerModel::FileContainerModel(chuck_inst* ck_,
                                       AudioProcessor* p_) :
                                        canBeEdited(true)
{
    ck = ck_;
    processor = p_;
    ScopedPointer<Random> random = new Random();
    uniqueFileContainerId = random->nextInt();
    
    std::stringstream ss;
    ss << uniqueFileContainerId;
    std::string uniqueFileContainerIdAsString = ss.str();
    
    fileChooser = new FileChooser("Open Chuck File", File::nonexistent, "*.ck");
    
    for (int i=0; i<8; i++)
        knobParameters.push_back( processor->getParameters().getUnchecked(i) );

}

void FileContainerModel::addShred()
{
    chuck_result result = libchuck_add_shred(ck, filePath.toRawUTF8(), codeDocument.getAllContent().toRawUTF8());
    std::cout << "result type: " << result.type << " result id" << result.shred_id << "\n";
    //libchuck_add_shred(ck, fileChooser->getFullPathName().toRawUTF8(),
    //codeEditorDemo->codeDocument.getAllContent().toRawUTF8());
    if(result.type == chuck_result::OK || result.type == chuck_result::ERR_TIMEOUT)
        // TODO ask spencer why it's returning error timeout and fix that
    {
        shredIds.push_back(result.shred_id);
        String txt = "shred with Id: " + String(shredIds.back()) + " added";
        //ConsoleGlobal::Instance()->addText(txt);
    }
    else
    {
        std::string resStr(libchuck_last_error_string(ck));
        std::cout<<"problem add shred:" + resStr << "\n";
        ConsoleGlobal::Instance()->addText(resStr);
        //CONSOLE ADD TEXT
        
    }
}

void FileContainerModel::removeLastShred()
{
    //std::cout<< "remove last shred called";
    std::cout<<"shredIds size:" << shredIds.size() << "\n";

    if( shredIds.size() > 0 )
    {
        std::cout<<"shredIds to be removed:" << shredIds.back() << "\n";

        removeShred( shredIds.back() );
        
        shredIds.pop_back();
    }
    else
    {
        ConsoleGlobal::Instance()->addText("No shreds to remove");
    }
}

void FileContainerModel::removeShred(int idNumber)
{
    //std::cout<<"shred to be removed:" << idNumber << "\n";

    chuck_result result = libchuck_remove_shred(ck, idNumber);
    if(result.type == chuck_result::OK)
    {
        std::cout<<"shred with Id removed "<< idNumber << "\n";
        ConsoleGlobal::Instance()->addText("shred with Id removed "+ String(idNumber));
    }
    else
    {
        std::string resStr(libchuck_last_error_string(ck));
        std::cout<<"problem removing shred:" + String(idNumber) << "\n";
        //ConsoleGlobal::Instance()->addText("problem removing shred:" + String(idNumber));
        ///getProcessor()->fileContainerManagerModel->addTextToConsole(resStr);
        //CONSOLE ADD TEXT
    }

}


void FileContainerModel::replaceShred()
{
    chuck_result result = libchuck_replace_shred( ck, shredIds.back(), filePath.toRawUTF8(),
                                               codeDocument.getAllContent().toRawUTF8() );
    if( result.type == chuck_result::OK )
    {
        shredIds.pop_back();
        shredIds.push_back( result.shred_id );
    }
    
}
void FileContainerModel::removeAllShreds()
{
    
    while ( !shredIds.empty() )
    {
        removeLastShred();
    }
    
    //Horrible hack. Remove after finding out why libchuck_remove_shred is not returning chuck_result::OK
    for ( int i = 0; i<20; i++ )
    {
        removeShred(i);
    }
}

void FileContainerModel::openBrowser()
{
    if ( fileChooser->browseForFileToOpen() )
    {
        File chuckFile ( fileChooser->getResult() );
        fileName = chuckFile.getFileName();
        filePath = chuckFile.getFullPathName();
    }
    
}

CodeDocument& FileContainerModel::getCodeDocument()
{
    return codeDocument;
}

