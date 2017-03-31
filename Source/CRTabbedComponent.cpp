/*
  ==============================================================================

    CRTabbedComponent.cpp
    Created: 31 Mar 2017 12:04:49am
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#include "CRTabbedComponent.h"

CRTabbedComponent::CRTabbedComponent() : TabbedComponent(TabbedButtonBar::Orientation::TabsAtTop)
{
    
}

CRTabbedComponent::~CRTabbedComponent()
{
    
}

void CRTabbedComponent::popupMenuClickOnTab (int tabIndex, const String &tabName){
    PopupMenu m;
    m.addItem (1, "Remove");
    const int result = m.show();
    if (result == 0){
        // user dismissed the menu without picking anything
    }
    else if (result == 1)
    {
        removeTab(tabIndex);
    }
}



