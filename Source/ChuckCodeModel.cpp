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

    if(result.type == chuck_result::OK)
    {
        shredIds.insert( std::make_pair(result.shred_id, result.shred_id) );
        text = "adding shred: " + String(result.shred_id);
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
        std::cout << "remove last shred, id: " << shredIds.end()->first << std::endl;
        removeShred(shredIds.rbegin()->first);
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
        text = "removing shred: " + String( result.shred_id );
        shredIds.erase( shredIds.at( result.shred_id ) );
    }
    
    else
    {
        //std::string resStr(libchuck_last_error_string(ck));
        text = "problem removing shred:" + String(idNumber);
    }
    
    
    
    ConsoleComponent::getInstance()->addText(text);
    //if (consoleComponent)
    //consoleComponent->addText(text);
    /// listeners.call(&ConsoleComponent::consoleMessageCallback, text);
    
}

void ChuckCodeModel::removeAllShreds()
{
    while ( !shredIds.empty() )
        removeLastShred();
}


void ChuckCodeModel::replaceShred()
{
    String text;

    chuck_result result = libchuck_replace_shred( ck, shredIds.end()->first, filePath.toRawUTF8(),
                                               codeDocument.getAllContent().toRawUTF8() );
    int idNumber = result.shred_id;
    
    if( result.type == chuck_result::OK )
    {
        shredIds.erase( shredIds.at(idNumber) );
        shredIds.insert( std::make_pair(result.shred_id, result.shred_id) );
        //shredIds.removeLast();
        //shredIds.add( result.shred_id );
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

/*void ChuckCodeModel::openBrowser()
{
    if ( fileChooser->browseForFileToOpen() )
    {
        File chuckFile ( fileChooser->getResult() );
        fileName = chuckFile.getFileName();
        filePath = chuckFile.getFullPathName();
    }
    
}*/

CodeDocument& ChuckCodeModel::getCodeDocument()
{
    return codeDocument;
}
