/*
  ==============================================================================

    ChuckCodeManagerComponent.h
    Created: 14 Feb 2017 10:54:47pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#ifndef CODEDOCUMENTMANAGERCOMPONENT_H_INCLUDED
#define CODEDOCUMENTMANAGERCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "ChuckCodeModelManager.h"
#include "ChuckCodeComponent.h"
#include "CRTabbedComponent.h"
//==============================================================================
/*
*/


class ChuckCodeManagerComponent :   public Component,
                                    public CRTabbedComponentListener
{
    
public:
    ChuckCodeManagerComponent(ChuckCodeModelManager* modelManager);
    ~ChuckCodeManagerComponent();

    void paint (Graphics&) override;
    void resized() override;
    
    void addNewChuckCodeComponent(ChuckCodeModel* chuckCodeModel);
    void removeChuckCodeComponent(int tabIndex);
    
    void removeTabComponent(int tabIndex) override;
    void duplicateTabComponent(int tabIndex) override;

private:
    ChuckCodeModelManager* mModelManager;
    Array<ChuckCodeComponent*> chuckCodeComponents;

    CRTabbedComponent tabView;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChuckCodeManagerComponent)
};


#endif  // CODEDOCUMENTMANAGERCOMPONENT_H_INCLUDED
