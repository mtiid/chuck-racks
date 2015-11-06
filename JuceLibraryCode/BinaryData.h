/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_79031815_INCLUDED
#define BINARYDATA_H_79031815_INCLUDED

namespace BinaryData
{
    extern const char*   addcodeeditor_svg;
    const int            addcodeeditor_svgSize = 1406;

    extern const char*   addshredicon_svg;
    const int            addshredicon_svgSize = 1394;

    extern const char*   libchuck_a;
    const int            libchuck_aSize = 25039824;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 3;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
