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

class MainViewComponent : public Component
{
public:
    MainViewComponent();
    ~MainViewComponent();
    
    void paint (Graphics &);
    void resized();
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainViewComponent)
    
};

#endif /* defined(__ChuckRacks__MainViewComponent__) */
