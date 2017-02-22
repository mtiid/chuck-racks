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
    ParameterMapUI(AudioProcessor* processor_);
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
    EditableTextCustomComponent (ParameterMapUI& pm)  : owner (pm),
                                                        mapLabel()
    {
        // double click to edit the label text; single click handled below
        setEditable (false, true, false);
        setColour (textColourId, Colour(180, 180, 180));
        addChildComponent(mapLabel);
        mapLabel.setText("right-click to map", dontSendNotification);
        mapLabel.setBounds(180, 0, 200, 20);
        mapLabel.setInterceptsMouseClicks(false, false);
    }
    
    void mouseDown (const MouseEvent& event) override
    {
        if(event.mods.isRightButtonDown() || event.mods.isCtrlDown())
        {
            PopupMenu m;
            m.addItem (1, "Map");
            const int result = m.show();
            if (result == 0)
            {
                // user dismissed the menu without picking anything
            }
            else if (result == 1)
            {
                owner.updateParamMap(row);
            }
            mapLabel.setVisible(false);
        }else{
        // single click on the label should simply select the row
        //owner.table.selectRowsBasedOnModifierKeys (row, event.mods, false);
            Label::mouseDown (event);
        }
    }
        
    void mouseEnter (const MouseEvent& event) override
    {
        mapLabel.setVisible(true);
    }
    
    void mouseExit (const MouseEvent& event) override
    {
        mapLabel.setVisible(false);
    }
    
    void textWasEdited() override
    {
        owner.setText (columnId, row, getText());
    }
    
    // This is called when we may need to update our contents
    void setRowAndColumn (const int newRow, const int newColumn)
    {
        row = newRow;
        columnId = newColumn;
        setText (owner.getText(columnId, row), dontSendNotification);
    }
    
private:
    ParameterMapUI& owner;
    int row, columnId;
    Label mapLabel;
    
};

#endif  // PARAMETERMAPUI_H_INCLUDED
