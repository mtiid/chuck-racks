/*
  ==============================================================================

    CRTabbedComponent.h
    Created: 31 Mar 2017 12:04:49am
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#ifndef CRTABBEDCOMPONENT_H_INCLUDED
#define CRTABBEDCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class CRTabbedComponent : public TabbedComponent
{
    
public:
    CRTabbedComponent();
    ~CRTabbedComponent();
    
    void popupMenuClickOnTab (int tabIndex, const String &tabName) override;
    
private:
    
};



#endif  // CRTABBEDCOMPONENT_H_INCLUDED
