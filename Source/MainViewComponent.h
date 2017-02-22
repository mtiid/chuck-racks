//
//  MainViewComponent.h
//  ChuckRacks
//
//  Created by Rodrigo Sena on 10/22/15.
//
//

#ifndef __ChuckRacks__MainViewComponent__
#define __ChuckRacks__MainViewComponent__

#include "../JuceLibraryCode/JuceHeader.h"
#include "EditorPanelUI.h"
#include "ParameterMapUI.h"
#include "PluginProcessor.h"

class MainViewComponent : public Component
{
public:
    MainViewComponent(ChuckRacksAudioProcessor* processor_);
    ~MainViewComponent();
    
    void paint (Graphics &);
    void resized();
    
    void toggleParamListVisibility();
    void addNewChuckCodeComponent(ChuckCodeModel* chuckCodeModel);
    
private:
    ChuckRacksAudioProcessor* processor;
    
    StretchableLayoutManager verticalLayout;
    StretchableLayoutResizerBar verticalDividerBar;
    
    EditorPanelUI editorArea;    
    ParameterMapUI parameterUI;
    
    void refresh(bool paramListVisible);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainViewComponent)
    
};

#endif /* defined(__ChuckRacks__MainViewComponent__) */
