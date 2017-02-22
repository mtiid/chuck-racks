/*
 ==============================================================================
 
 ParameterMapUI.cpp
 Created: 24 Jan 2017 10:37:37pm
 Author:  Jordan Hochenbaum
 
 ==============================================================================
 */

#include "ParameterMapUI.h"

ParameterMapUI::ParameterMapUI(AudioProcessor* processor_) : numRows(0)
{
    processor = static_cast<ChuckRacksAudioProcessor*>(processor_);
    parameterListModel = processor->getParameterListModel();
    addAndMakeVisible(table);
    table.setRowHeight (20);
    table.setModel (this);
    
    // give it a border
    //table.setColour (ListBox::outlineColourId, Colours::black);
    //table.setOutlineThickness (1);
    table.getHeader().addColumn(String(), 1, 22, TableHeaderComponent::notSortable);
    table.getHeader().addColumn("Parameter Name", 2, 280, TableHeaderComponent::notSortable);
    
    table.setAutoSizeMenuOptionShown(false);
    table.getHeader().setStretchToFitActive(true);
    
    ScopedPointer<XmlElement> addShredSVGUp(XmlDocument::parse(BinaryData::addshrediconUp_svg));
    ScopedPointer<XmlElement> addShredSVGDown(XmlDocument::parse(BinaryData::addshrediconDown_svg));
    addNewButton = new DrawableButton("Add New Parameter", DrawableButton::ButtonStyle::ImageFitted);
    addNewButton->setImages(Drawable::createFromSVG(*addShredSVGUp),
                            nullptr,
                            Drawable::createFromSVG(*addShredSVGDown),
                            nullptr,
                            Drawable::createFromSVG(*addShredSVGDown),
                            nullptr,
                            Drawable::createFromSVG(*addShredSVGUp),
                            nullptr);
    
    addNewButton->setColour(DrawableButton::backgroundOnColourId, Colour(0.0f,0.0f,0.0f,0.0f));
    addAndMakeVisible(addNewButton);
    addNewButton->addListener(this);
}

ParameterMapUI::~ParameterMapUI(){
    
}

void ParameterMapUI::paint (Graphics& g){
    g.fillAll(Colour(50, 53, 64));
}

void ParameterMapUI::resized(){
    table.setBoundsInset (BorderSize<int> (1));
    int bSize = table.getHeader().getHeight()*0.9;
    int xPos = (table.getHeader().getColumnWidth(1)*0.5) - (bSize*0.5);
    addNewButton->setBounds(xPos, 2, bSize, bSize);
}

void ParameterMapUI::buttonClicked (Button* buttonThatWasClicked){
    if (buttonThatWasClicked == addNewButton) {
        addRow();
    }
}

void ParameterMapUI::addRow(){
    processor->mapNewParam();
    table.resized();
}

void ParameterMapUI::updateParamMap(int num){
    processor->setParameterNotifyingHost(num,
                                         processor->getParamValue(parameterListModel->at(num)));
}

// This is overloaded from TableListBoxModel, and must return the total number of rows in our table
int ParameterMapUI::getNumRows()
{
    return parameterListModel->size();
}

// This is overloaded from TableListBoxModel, and should fill in the background of the whole row
void ParameterMapUI::paintRowBackground (Graphics& g, int rowNumber,
                                         int /*width*/, int /*height*/,
                                         bool rowIsSelected)
{
    g.fillAll(Colour(38, 40, 49));
}

// This is overloaded from TableListBoxModel, and must paint any cells that aren't using custom
// components.
void ParameterMapUI::paintCell (Graphics& g, int rowNumber, int columnId,
                                int width, int height, bool /*rowIsSelected*/)
{
    g.setColour (Colours::black.withAlpha (0.2f));
    g.fillRect (width - 1, 0, 1, height);
    
    g.setFont (font);
    
    Justification justification = Justification::centredLeft;
    
    if ( parameterListModel->at(rowNumber).isNotEmpty() )
    {
        String text;
        if (columnId == 1){
            justification = Justification::centred;
            g.setColour (Colour(62, 172, 133));
            text = String(rowNumber);
        }
        
        else if (columnId == 2){
            text = parameterListModel->at(rowNumber);
        }else{
            text = String();
        }
        
        g.drawText (text, 2, 0, width - 4, height, justification, true);
    }
}

// This is overloaded from TableListBoxModel, and must update any custom components that we're using
Component* ParameterMapUI::refreshComponentForCell (int rowNumber, int columnId, bool /*isRowSelected*/,
                                                    Component* existingComponentToUpdate)
{
    if (columnId == 1) // The num column do not have a custom component
    {
        jassert (existingComponentToUpdate == nullptr);
        return nullptr;
    }
    
    else if(columnId ==2){
        // Param name column uses the custom Label component
        EditableTextCustomComponent* textLabel = static_cast<EditableTextCustomComponent*> (existingComponentToUpdate);
        
        if (textLabel == nullptr)
            textLabel = new EditableTextCustomComponent (*this);
        
        textLabel->setRowAndColumn (rowNumber, columnId);
        return textLabel;
    }else{
        jassert (existingComponentToUpdate == nullptr);
        return nullptr;
    }
}

String ParameterMapUI::getText (const int columnNumber, const int rowNumber) const
{
    return parameterListModel->find(rowNumber)->second;
}

void ParameterMapUI::setText (const int columnNumber, const int rowNumber, const String& newText)
{
    String text = newText;
    
    if (text.isEmpty())
        text = "not assigned";
    
    parameterListModel->find(rowNumber)->second = text;
    processor->updateParamNames(rowNumber, text);
    table.deselectRow(rowNumber);
}
