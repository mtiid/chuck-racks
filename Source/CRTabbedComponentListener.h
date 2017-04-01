/*
  ==============================================================================

    CRTabbedComponentListener.h
    Created: 31 Mar 2017 12:49:32am
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#ifndef CRTABBEDCOMPONENTLISTENER_H_INCLUDED
#define CRTABBEDCOMPONENTLISTENER_H_INCLUDED

class CRTabbedComponentListener{
    
public:

    CRTabbedComponentListener(){};
    virtual ~CRTabbedComponentListener(){};
    
    virtual void removeTabComponent(int tabIndex){};
    virtual void duplicateTabComponent(int tabIndex){};
    
private:
    
};



#endif  // CRTABBEDCOMPONENTLISTENER_H_INCLUDED
