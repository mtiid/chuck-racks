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
}

ChuckCodeModel::~ChuckCodeModel(){
    listeners.clear();
}

void ChuckCodeModel::addShred()
{
    String text;
    chuck_result result = libchuck_add_shred(ck, filePath.toRawUTF8(), codeDocument.getAllContent().toRawUTF8());
    std::cout << "result type: " << result.type << " result id" << result.shred_id << "\n";
    //libchuck_add_shred(ck, fileChooser->getFullPathName().toRawUTF8(),
    //codeEditorDemo->codeDocument.getAllContent().toRawUTF8());
    if(result.type == chuck_result::OK || result.type == chuck_result::ERR_TIMEOUT)
        // TODO ask spencer why it's returning error timeout and fix that
    {
        shredIds.push_back(result.shred_id);
        text = "shred with Id: " + String(shredIds.back()) + " added";
        
        //ConsoleGlobal::Instance()->addText(txt);
    }
    else
    {
        text = libchuck_last_error_string(ck);
        //std::cout<<"problem add shred:" + resStr << "\n";
        //ConsoleGlobal::Instance()->addText(resStr);
        //CONSOLE ADD TEXT
        
    }
    
    if (consoleComponent)
        consoleComponent->addText(text);
    ///listeners.call(&ConsoleComponent::consoleMessageCallback, text);

}

void ChuckCodeModel::removeLastShred()
{
    //std::cout<< "remove last shred called";
    std::cout<<"shredIds size:" << shredIds.size() << "\n";
    String text;
    
    if( shredIds.size() > 0 )
    {
        text = "shredId to be removed:" + String(shredIds.back());

        removeShred( shredIds.back() );
        
        shredIds.pop_back();
    }
    else
    {
       text = "No shreds to remove";
        //ConsoleGlobal::Instance()->addText("No shreds to remove");
    }
   /// listeners.call(&ConsoleComponent::consoleMessageCallback, text);
}

void ChuckCodeModel::removeShred(int idNumber)
{
    String text;
    
    chuck_result result = libchuck_remove_shred(ck, idNumber);
    if(result.type == chuck_result::OK)
    {
        std::cout<<"shred with Id removed "<< idNumber << "\n";
        text = "shred with Id removed "+ String(idNumber);
        //ConsoleGlobal::Instance()->addText("shred with Id removed "+ String(idNumber));
    }
    else
    {
        std::string resStr(libchuck_last_error_string(ck));
        text = "problem removing shred:" + String(idNumber);
        //ConsoleGlobal::Instance()->addText("problem removing shred:" + String(idNumber));
        ///getProcessor()->fileContainerManagerModel->addTextToConsole(resStr);
        //CONSOLE ADD TEXT
    }
    
   /// listeners.call(&ConsoleComponent::consoleMessageCallback, text);

}


void ChuckCodeModel::replaceShred()
{
    chuck_result result = libchuck_replace_shred( ck, shredIds.back(), filePath.toRawUTF8(),
                                               codeDocument.getAllContent().toRawUTF8() );
    if( result.type == chuck_result::OK )
    {
        shredIds.pop_back();
        shredIds.push_back( result.shred_id );
    }
    
}
void ChuckCodeModel::removeAllShreds()
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

void ChuckCodeModel::addListener(ConsoleComponent* listenerToAdd){
    consoleComponent = listenerToAdd;
    //listeners.add(listenerToAdd);
}

void ChuckCodeModel::removeListener(ConsoleComponent* listenerToRemove){
    delete consoleComponent;
    //listeners.remove(listenerToRemove);
}

