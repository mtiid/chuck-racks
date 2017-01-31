/*
  ==============================================================================

    ParameterMapUI.h
    Created: 24 Jan 2017 10:37:37pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#ifndef PARAMETERMAPUI_H_INCLUDED
#define PARAMETERMAPUI_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include <map>
#include "PluginProcessor.h"

class ParameterMapUI :  public Component,
                        public TableListBoxModel,
                        public Button::Listener
{
    
public:
    ParameterMapUI(AudioProcessor* p_);
    ~ParameterMapUI();
    
    void paint (Graphics &) override;
    void resized() override;
    
    void addRow();
    void updateParamMap(int num);
    
    // TableListBoxModel overrides
    int getNumRows () override;
    void paintRowBackground (Graphics &, int rowNumber,
                             int width, int height,
                             bool rowIsSelected) override;
    void paintCell (Graphics &, int rowNumber,
                    int columnId, int width,
                    int height, bool rowIsSelected) override;
    
    Component* refreshComponentForCell (int rowNumber, int columnId, bool /*isRowSelected*/,
                                        Component* existingComponentToUpdate) override;
    
    void setText (const int columnNumber, const int rowNumber, const String& newText);
    String getText (const int columnNumber, const int rowNumber) const;
    TableListBox table;
    
    void buttonClicked (Button*) override;
    
private:
    //ScopedPointer<TextButton> addNewButton;
    ScopedPointer<DrawableButton> addNewButton;
    
    Font font;
    int numRows;
    
    ChuckRacksAudioProcessor* processor;
    std::map<int, String>* parameterListModel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ParameterMapUI)
};

//==============================================================================
// This is a custom Label component, which we use for the table's editable text columns.
class EditableTextCustomComponent  : public Label
{
public:
    EditableTextCustomComponent (ParameterMapUI& pm)  : owner (pm)
    {
        // double click to edit the label text; single click handled below
        setEditable (false, true, false);
        setColour (textColourId, Colours::black);
    }
    
    void mouseDown (const MouseEvent& event) override
    {
        // single click on the label should simply select the row
        owner.table.selectRowsBasedOnModifierKeys (row, event.mods, false);
        
        Label::mouseDown (event);
    }
    
    void textWasEdited() override
    {
        owner.setText (columnId, row, getText());
        //std::cout << getText() << std::endl;
    }
    
    // Our demo code will call this when we may need to update our contents
    void setRowAndColumn (const int newRow, const int newColumn)
    {
        row = newRow;
        columnId = newColumn;
        setText (owner.getText(columnId, row), dontSendNotification);
    }
    
private:
    ParameterMapUI& owner;
    int row, columnId;
    
    
};

//==============================================================================
// This is a custom Button component, which we use for the table's parameter map trigger column.
class ButtonCustomComponent  : public Button
{
public:
    ButtonCustomComponent (ParameterMapUI& pm)  : Button(String()), owner (pm)
    {
    }
    
    
    void clicked(){
        owner.updateParamMap(row);
    }
    
    // Our demo code will call this when we may need to update our contents
    void setRowAndColumn (const int newRow, const int newColumn)
    {
        row = newRow;
        columnId = newColumn;
    }
    
    void paintButton (Graphics &g, bool isMouseOverButton, bool isButtonDown){
        Colour colourToSet = Colour(62, 172, 133).withAlpha(0.2f);
        if (isMouseOverButton) {
            g.setColour(Colours::grey.withAlpha(0.6f));
        }
        
        if(isButtonDown){
            g.setColour(colourToSet.withAlpha(0.8f));
        }
        g.fillRect(0, 0, getWidth(), getHeight());
    }
    
private:
    ParameterMapUI& owner;
    int row, columnId;
    
    
};


#endif  // PARAMETERMAPUI_H_INCLUDED
