//
//  ChuckCodeModel.cpp
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/22/15.
//
//

#include "ChuckCodeModel.h"
#include "PluginProcessor.h"
#include <sstream>

ChuckCodeModel::ChuckCodeModel(chuck_inst* ck_,
                                AudioProcessor* p_) :
                                canBeEdited(true),
                                fileName("Untitled")
{
    ck = ck_;
    processor = p_;
    ScopedPointer<Random> random = new Random();
    uniqueFileContainerId = random->nextInt();
    
    std::stringstream ss;
    ss << uniqueFileContainerId;
    std::string uniqueFileContainerIdAsString = ss.str();
    
    fileChooser = new FileChooser("Open Chuck File", File::nonexistent, "*.ck");
}

ChuckCodeModel::~ChuckCodeModel(){
}

void ChuckCodeModel::addShred()
{
    String text;
    chuck_result result = libchuck_add_shred(ck, filePath.toRawUTF8(), codeDocument.getAllContent().toRawUTF8());
    std::cout << "result type: " << result.type << " result id " << result.shred_id << "\n";

    if(result.type == chuck_result::OK || result.type == chuck_result::ERR_TIMEOUT)
        // TODO ask spencer why it's returning error timeout and fix that
    {
        shredIds.add(result.shred_id);
        //shredIds.push_back(result.shred_id);
        text = "shred with Id: " + String(shredIds.getLast()) + " added";
    }
    else
    {
        text = libchuck_last_error_string(ck);
       // std::cout<<"problem add shred:" + resStr << "\n";
        //ConsoleGlobal::Instance()->addText(resStr);
        //CONSOLE ADD TEXT
        
    }
    ConsoleComponent::getInstance()->addText(text);
    //if (consoleComponent)
    //    consoleComponent->addText("hey there");
    ///listeners.call(&ConsoleComponent::consoleMessageCallback, text);

}

void ChuckCodeModel::removeLastShred()
{
    String text;
    
    if( shredIds.size() > 0 )
    {
        text = "shredId to be removed:" + String(shredIds.getLast());
        /// \todo update once we're storing actual shred id
        removeShred( shredIds.size()-1 );
        shredIds.removeLast();
    }
    else
    {
       text = "No shreds to remove";
        //ConsoleGlobal::Instance()->addText("No shreds to remove");
    }
    
    ConsoleComponent::getInstance()->addText(text);
    
    //if (consoleComponent)
    //    consoleComponent->addText(text);
   /// listeners.call(&ConsoleComponent::consoleMessageCallback, text);
}

void ChuckCodeModel::removeShred(int idNumber)
{
    String text;
    
    chuck_result result = libchuck_remove_shred(ck, idNumber);
    
    if(result.type == chuck_result::OK)
    {
        //std::cout<<"shred with Id removed "<< idNumber << "\n";
        text = "shred with Id removed "+ String(idNumber);
    }
    else
    {
        //std::string resStr(libchuck_last_error_string(ck));
        //text = "problem removing shred:" + String(idNumber);
        /// \todo add back when once correct shred ids are returned correctly from libchuck
    }
    
    
    shredIds.remove(idNumber);
    
    ConsoleComponent::getInstance()->addText(text);
    //if (consoleComponent)
        //consoleComponent->addText(text);
   /// listeners.call(&ConsoleComponent::consoleMessageCallback, text);

}

void ChuckCodeModel::removeAllShreds()
{
    /// \todo use actual shred ids once that's being returned correctly from libchuck
    /*for (int i=0; i<shredIds.size(); i++) {
        removeShred(i+1);
    }*/
    
    for (int i=0; i<20; i++){
        removeShred(i);
    }
}


void ChuckCodeModel::replaceShred()
{
    String text;

    chuck_result result = libchuck_replace_shred( ck, shredIds.getLast(), filePath.toRawUTF8(),
                                               codeDocument.getAllContent().toRawUTF8() );
    int idNumber = result.shred_id;
    
    if( result.type == chuck_result::OK )
    {
        shredIds.removeLast();
        shredIds.add( result.shred_id );
        text = "shred with Id replaced "+ String(idNumber);
    }
    else
    {
        text = "problem replacing shred:" + String(idNumber);
    }
    
    ConsoleComponent::getInstance()->addText(text);
    //if (consoleComponent != nullptr)
    //    consoleComponent->addText(text);
    
}

void ChuckCodeModel::openBrowser()
{
    if ( fileChooser->browseForFileToOpen() )
    {
        File chuckFile ( fileChooser->getResult() );
        fileName = chuckFile.getFileName();
        filePath = chuckFile.getFullPathName();
    }
    
}

CodeDocument& ChuckCodeModel::getCodeDocument()
{
    return codeDocument;
}
