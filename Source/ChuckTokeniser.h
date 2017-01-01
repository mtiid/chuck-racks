//
//  ChuckTokeniser.h
//  ChuckRacks
//
//  Created by Rodrigo Sena on 4/5/15.
//
//

#ifndef __ChuckRacks__ChuckTokeniser__
#define __ChuckRacks__ChuckTokeniser__

//#include <iostream>


#include "../JuceLibraryCode/JuceHeader.h"


class ChuckTokeniser : public CodeTokeniser
{

public:
    //==============================================================================
    ChuckTokeniser();
    ~ChuckTokeniser();
    
    //==============================================================================
    int readNextToken (CodeDocument::Iterator&) override;
    /** This is a handy method for checking whether a string is a c++ reserved keyword. */
    static bool isReservedKeyword (const String& token) noexcept;
    
    CodeEditorComponent::ColourScheme getDefaultColourScheme() override;
    
    /** The token values returned by this tokeniser. */
    enum TokenType
    {
        tokenType_error = 0,
        
        tokenType_keyword,
        tokenType_defaultClass,
        tokenType_defaultUGen,
        tokenType_customClass,
        
        tokenType_comment,
        tokenType_operator,
        tokenType_identifier,
        tokenType_integer,
        tokenType_float,
        tokenType_string,
        tokenType_bracket,
        tokenType_punctuation,
        tokenType_preprocessor,
        
        tokenType_notReserved
        
        
        
    };
    
    
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChuckTokeniser)
    
    
    
    
    
};

#endif /* defined(__ChuckRacks__ChuckTokeniser__) */

