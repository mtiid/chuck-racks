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
#include "CRTabbedComponentListener.h"

class CRTabbedComponent : public TabbedComponent
{
    
public:
    CRTabbedComponent();
    ~CRTabbedComponent();
    
    void popupMenuClickOnTab (int tabIndex, const String &tabName) override;
    
    void addListener(CRTabbedComponentListener* comp){listeners.add(comp);};
    
private:
    ListenerList<CRTabbedComponentListener> listeners;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CRTabbedComponent);

};



#endif  // CRTABBEDCOMPONENT_H_INCLUDED
