/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_79031815_INCLUDED
#define BINARYDATA_H_79031815_INCLUDED

namespace BinaryData
{
    extern const char*   addshrediconUp_svg;
    const int            addshrediconUp_svgSize = 891;

    extern const char*   addshrediconDown_svg;
    const int            addshrediconDown_svgSize = 906;

    extern const char*   removeAllShredUp_svg;
    const int            removeAllShredUp_svgSize = 990;

    extern const char*   removeAllShredDown_svg;
    const int            removeAllShredDown_svgSize = 1005;

    extern const char*   addcodeeditorUp_svg;
    const int            addcodeeditorUp_svgSize = 1114;

    extern const char*   addcodeeditorDown_svg;
    const int            addcodeeditorDown_svgSize = 1130;

    extern const char*   libchuck_a;
    const int            libchuck_aSize = 25039824;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 7;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
