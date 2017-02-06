#include "ChuckTokeniser.h"


static const char* const keywords[] =
{
    "int",
    "float",
    "time",
    "dur",
    "polar",
    "complex",
    "void",
    "same",
    
    "if",
    "else",
    "while",
    "do",
    "until",
    "for",
    "break",
    "continue",
    "return",
    "switch",
    "repeat",
    
    "class",
    "extends",
    "public",
    "static",
    "pure",
    "this",
    "super",
    "interface",
    "implements",
    "protected",
    "private",
    
    "function",
    "fun",
    "spork",
    "const",
    "new",
    
    "now",
    "true",
    "false",
    "maybe",
    "null",
    "NULL",
    "me",
    "pi",
    
    "samp",
    "ms",
    "second",
    "minute",
    "hour",
    "day",
    "week",
    
    "dac",
    "adc",
    "blackhole",
    "chout",
    "cherr",
    
    nullptr };

static const char* const defaultClasses[] =
{
    "Object",
    "string",
    "UAnaBlob",
    "Shred",
    "Thread",
    "Class",
    "Event",
    "IO",
    "FileIO",
    "StdOut",
    "StdErr",
    "Windowing",
    "Machine",
    "Std",
    "KBHit",
    "ConsoleInput",
    "StringTokenizer",
    "Math",
    "OscSend",
    "OscEvent",
    "OscRecv",
    "OscIn",
    "OscOut",
    "OscMsg",
    "MidiMsg",
    "MidiIn",
    "MidiOut",
    "MidiRW",
    "MidiMsgIn",
    "MidiMsgOut",
    "MidiFileIn",
    "HidMsg",
    "Hid",
    "RegEx",
    "SerialIO",
    nullptr };

static const char* const defaultUGens[] =
{
    "UGen",
    "UAna",
    "Osc",
    "Phasor",
    "SinOsc",
    "TriOsc",
    "SawOsc",
    "PulseOsc",
    "SqrOsc",
    "GenX",
    "Gen5",
    "Gen7",
    "Pan2",
    "Gen9",
    "Gen10",
    "Gen17",
    "CurveTable",
    "WarpTable",
    "Chubgraph",
    "Chugen",
    "UGen_Stereo",
    "UGen_Multi",
    "DAC",
    "ADC",
    "Mix2",
    "Gain",
    "Noise",
    "CNoise",
    "Impulse",
    "Step",
    "HalfRect",
    "FullRect",
    "DelayP",
    "SndBuf",
    "SndBuf2",
    "Dyno",
    "LiSa",
    "FilterBasic",
    "BPF",
    "BRF",
    "LPF",
    "HPF",
    "ResonZ",
    "BiQuad",
    "Teabox",
    "StkInstrument",
    "BandedWG",
    "BlowBotl",
    "BlowHole",
    "Bowed",
    "Brass",
    "Clarinet",
    "Flute",
    "Mandolin",
    "ModalBar",
    "Moog",
    "Saxofony",
    "Shakers",
    "Sitar",
    "StifKarp",
    "VoicForm",
    "FM",
    "BeeThree",
    "FMVoices",
    "HevyMetl",
    "PercFlut",
    "Rhodey",
    "TubeBell",
    "Wurley",
    "Delay",
    "DelayA",
    "DelayL",
    "Echo",
    "Envelope",
    "ADSR",
    "FilterStk",
    "OnePole",
    "TwoPole",
    "OneZero",
    "TwoZero",
    "PoleZero",
    "JCRev",
    "NRev",
    "PRCRev",
    "Chorus",
    "Modulate",
    "PitShift",
    "SubNoise",
    "WvIn",
    "WaveLoop",
    "WvOut",
    "WvOut2",
    "BLT",
    "BlitSquare",
    "Blit",
    "BlitSaw",
    "JetTabl",
    "Mesh2D",
    "FFT",
    "IFFT",
    "Flip",
    "pilF",
    "DCT",
    "IDCT",
    "FeatureCollector",
    "Centroid",
    "Flux",
    "RMS",
    "RollOff",
    "AutoCorr",
    "XCorr",
    "ZeroX",
    nullptr };

static const char* const customClasses[] =
{
    "PluginHost",
    "PluginParameters",
    nullptr
};

struct ChuckTokeniserFunctions
{
    static ChuckTokeniser::TokenType isReservedKeyword (String::CharPointerType token, const int tokenLength) noexcept
    {
        //keywords taken from https://github.com/ccrma/miniAudicle/blob/master/src/macosx/mASyntaxHighlighter.mm
                
        //implement one for Chugins
        
        //implement one for myPluginClasses
        
        for (int i = 0; keywords[i] != 0; ++i)
            if (token.compare (CharPointer_ASCII (keywords[i])) == 0)
                return ChuckTokeniser::tokenType_keyword;
        
        for (int i = 0; defaultClasses[i] != 0; ++i)
            if (token.compare (CharPointer_ASCII (defaultClasses[i])) == 0)
                return ChuckTokeniser::tokenType_defaultClass;

        for (int i = 0; defaultUGens[i] != 0; ++i)
            if (token.compare (CharPointer_ASCII (defaultUGens[i])) == 0)
                return ChuckTokeniser::tokenType_defaultUGen;
        
        for (int i = 0; customClasses[i] != 0; ++i)
            if (token.compare (CharPointer_ASCII (customClasses[i])) == 0)
                return ChuckTokeniser::tokenType_customClass;
        
        
        return ChuckTokeniser::tokenType_notReserved;
    }
    
    template <typename Iterator>
    static int parseIdentifier (Iterator& source) noexcept
    {
        int tokenLength = 0;
        String::CharPointerType::CharType possibleIdentifier [100];
        String::CharPointerType possible (possibleIdentifier);
        
        while (CppTokeniserFunctions::isIdentifierBody (source.peekNextChar()))
        {
            const juce_wchar c = source.nextChar();
            
            if (tokenLength < 20)
                possible.write (c);
            
            ++tokenLength;
        }
        
        if (tokenLength > 1 && tokenLength <= 16)
        {
            possible.writeNull();
            
            ChuckTokeniser::TokenType tTypeResult=isReservedKeyword (String::CharPointerType (possibleIdentifier), tokenLength);
            if (tTypeResult!=ChuckTokeniser::tokenType_notReserved)
                return tTypeResult;
        }
        
        return ChuckTokeniser::tokenType_identifier;
    }
    
    template <typename Iterator>
    static int parseNumber (Iterator& source)
    {
        const Iterator original (source);
        
        if (CppTokeniserFunctions::parseFloatLiteral (source))    return ChuckTokeniser::tokenType_float;
        source = original;
        
        if (CppTokeniserFunctions::parseHexLiteral (source))      return ChuckTokeniser::tokenType_integer;
        source = original;
        
        if (CppTokeniserFunctions::parseOctalLiteral (source))    return ChuckTokeniser::tokenType_integer;
        source = original;
        
        if (CppTokeniserFunctions::parseDecimalLiteral (source))  return ChuckTokeniser::tokenType_integer;
        source = original;
        
        return ChuckTokeniser::tokenType_error;
    }
    
    template <typename Iterator>
    static void skipComment (Iterator& source) noexcept
    {
        bool lastWasStar = false;
        
        for (;;)
        {
            const juce_wchar c = source.nextChar();
            
            if (c == 0 || (c == '/' && lastWasStar))
                break;
            
            lastWasStar = (c == '*');
        }
    }
    
    template <typename Iterator>
    static int readNextToken (Iterator& source)
    {
        source.skipWhitespace();
        
        const juce_wchar firstChar = source.peekNextChar();
        
        switch (firstChar)
        {
            case 0:
                break;
                
            case '0':   case '1':   case '2':   case '3':   case '4':
            case '5':   case '6':   case '7':   case '8':   case '9':
            case '.':
            {
                int result = parseNumber (source);
                
                if (result == ChuckTokeniser::tokenType_error)
                {
                    source.skip();
                    
                    if (firstChar == '.')
                        return ChuckTokeniser::tokenType_punctuation;
                }
                
                return result;
            }
                
            case ',':
            case ';':
            case ':':
                source.skip();
                return ChuckTokeniser::tokenType_punctuation;
                
            case '(':   case ')':
            case '{':   case '}':
            case '[':   case ']':
                source.skip();
                return ChuckTokeniser::tokenType_bracket;
                
            case '"':
            case '\'':
                CppTokeniserFunctions::skipQuotedString (source);
                return ChuckTokeniser::tokenType_string;
                
            case '+':
                source.skip();
                CppTokeniserFunctions::skipIfNextCharMatches (source, '+', '=');
                return ChuckTokeniser::tokenType_operator;
                
            case '-':
            {
                source.skip();
                int result = CppTokeniserFunctions::parseNumber (source);
                
                if (source.peekNextChar() == '-')
                {
                    source.skipToEndOfLine();
                    return ChuckTokeniser::tokenType_comment;
                }
                
                if (result == ChuckTokeniser::tokenType_error)
                {
                    CppTokeniserFunctions::skipIfNextCharMatches (source, '-', '=');
                    return ChuckTokeniser::tokenType_operator;
                }
                
                return result;
            }
                
            case '*':   case '%':
            case '=':   case '!':
                source.skip();
                CppTokeniserFunctions::skipIfNextCharMatches (source, '=');
                return ChuckTokeniser::tokenType_operator;
                
            case '?':
            case '~':
                source.skip();
                return ChuckTokeniser::tokenType_operator;
                
            case '<':   case '>':
            case '|':   case '&':   case '^':
                source.skip();
                CppTokeniserFunctions::skipIfNextCharMatches (source, firstChar);
                CppTokeniserFunctions::skipIfNextCharMatches (source, '=');
                return ChuckTokeniser::tokenType_operator;
            case '/':
            {
                source.skip();
                juce_wchar nextChar = source.peekNextChar();
                
                if (nextChar == '/')
                {
                    source.skipToEndOfLine();
                    return ChuckTokeniser::tokenType_comment;
                }
                
                if (nextChar == '*')
                {
                    source.skip();
                    skipComment (source);
                    return ChuckTokeniser::tokenType_comment;
                }
                
                if (nextChar == '=')
                    source.skip();
                
                return ChuckTokeniser::tokenType_operator;
            }
            default:
                if (CppTokeniserFunctions::isIdentifierStart (firstChar))
                    return parseIdentifier (source);
                
                source.skip();
                break;
        }
        
        return ChuckTokeniser::tokenType_error;
    }
};

//==============================================================================
ChuckTokeniser::ChuckTokeniser() {}
ChuckTokeniser::~ChuckTokeniser() {}

int ChuckTokeniser::readNextToken (CodeDocument::Iterator& source)
{
    return ChuckTokeniserFunctions::readNextToken (source);
}

CodeEditorComponent::ColourScheme ChuckTokeniser::getDefaultColourScheme()
{
    static const CodeEditorComponent::ColourScheme::TokenType types[] =
    {
        { "Error",          Colour (0xffcc0000) },
        
        { "Keyword",        Colour (0xff0000cc) },
        { "DefaultClass",   Colour (0xffaa0000) },
        { "DefaultUGen",    Colour (0xffb83de7) },
        { "CustomClass",    Colour (0xff555500) },
        
        { "Comment",        Colour (0xff6f9d35) },
        { "Operator",       Colour (0xff225500) },
        { "Identifier",     Colour (0xff000000) },
        { "Integer",        Colour (0xffffaa00) },
        { "Float",          Colour (0xffffaa00) },
        { "String",         Colour (0xff990099) },
        { "Bracket",        Colour (0xff000055) },
        { "Punctuation",    Colour (0xff004400) }
        
        /*
        tokenType_error = 0,
        
        tokenType_keyword,
        tokenType_defaultClass,
        tokenType_defaultUGen,
         
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
         */
    };
    
    CodeEditorComponent::ColourScheme cs;
    
    for (unsigned int i = 0; i < sizeof (types) / sizeof (types[0]); ++i)  // (NB: numElementsInArray doesn't work here in GCC4.2)
        cs.set (types[i].name, types[i].colour);
    
    return cs;
}
