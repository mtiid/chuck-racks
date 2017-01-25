/*
  ==============================================================================

    ParameterMapUI.cpp
    Created: 24 Jan 2017 10:37:37pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#include "ParameterMapUI.h"

ParameterMapUI::ParameterMapUI() : numRows(512)
{
    
    addAndMakeVisible(table);
    table.setRowHeight (20);
    table.setModel (this);
    
    // give it a border
    //table.setColour (ListBox::outlineColourId, Colours::black);
    //table.setOutlineThickness (1);
    table.getHeader().addColumn("#", 1, 30, TableHeaderComponent::defaultFlags);
    table.getHeader().addColumn("Parameter Name", 2, 300, TableHeaderComponent::notSortable);
    
    //parameterListModel.insert(std::make_pair(0, String("Cutoff")));
    for (int i=0; i<numRows; i++) {
        parameterListModel.insert(std::make_pair(i, String("not assigned")));
    }
    
    table.setAutoSizeMenuOptionShown(false);
    //table.getHeader().setStretchToFitActive(true);
    
}

ParameterMapUI::~ParameterMapUI(){
    
}

void ParameterMapUI::paint (Graphics& g){
    g.fillAll(Colour(40, 43, 34));
    //g.fillAll(Colours::black.withAlpha (0.8f));
}

void ParameterMapUI::resized(){
    table.setBoundsInset (BorderSize<int> (1));
}

// This is overloaded from TableListBoxModel, and must return the total number of rows in our table
int ParameterMapUI::getNumRows()
{
    return numRows;
}

// This is overloaded from TableListBoxModel, and should fill in the background of the whole row
void ParameterMapUI::paintRowBackground (Graphics& g, int rowNumber,
                                         int /*width*/, int /*height*/,
                                         bool rowIsSelected)
{
   
    if (rowIsSelected)
        g.fillAll (Colours::lightslategrey);
    else if (rowNumber % 2)
        g.fillAll (Colour(100, 106, 127));
    else
        g.fillAll(Colour(28, 30, 37));
}

// This is overloaded from TableListBoxModel, and must paint any cells that aren't using custom
// components.
void ParameterMapUI::paintCell (Graphics& g, int rowNumber, int columnId,
                int width, int height, bool /*rowIsSelected*/)
{
    g.setColour (Colours::black.withAlpha (0.2f));
    g.fillRect (width - 1, 0, 1, height);
    
    g.setColour (Colours::black);
    g.setFont (font);

    
    if ( parameterListModel.at(rowNumber).isNotEmpty() )
    {
        String text;
        if (columnId == 1){
            text = String(rowNumber);
        }
        
        else if (columnId == 2){
            text = parameterListModel.at(rowNumber);
        }
        
        g.drawText (text, 2, 0, width - 4, height, Justification::centredLeft, true);
    }
}

// This is overloaded from TableListBoxModel, and must update any custom components that we're using
Component* ParameterMapUI::refreshComponentForCell (int rowNumber, int columnId, bool /*isRowSelected*/,
                                    Component* existingComponentToUpdate)
{
    if (columnId == 1) // The ID and Length columns do not have a custom component
    {
        jassert (existingComponentToUpdate == nullptr);
        return nullptr;
    }
    
    
    // The other columns are editable text columns, for which we use the custom Label component
    EditableTextCustomComponent* textLabel = static_cast<EditableTextCustomComponent*> (existingComponentToUpdate);
    
    // same as above...
    if (textLabel == nullptr)
        textLabel = new EditableTextCustomComponent (*this);
    
    textLabel->setRowAndColumn (rowNumber, columnId);
    return textLabel;
}

String ParameterMapUI::getText (const int columnNumber, const int rowNumber) const
{
    return parameterListModel.find(rowNumber)->second;
    //return dataList->getChildElement (rowNumber)->getStringAttribute ( getAttributeNameForColumnId(columnNumber));
}

void ParameterMapUI::setText (const int columnNumber, const int rowNumber, const String& newText)
{
    //const String& columnName = table.getHeader().getColumnName (columnNumber);
    parameterListModel.find(rowNumber)->second = newText;
    //dataList->getChildElement (rowNumber)->setAttribute (columnName, newText);
}
