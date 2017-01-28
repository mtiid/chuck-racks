/*
  ==============================================================================

    ParameterMapUI.cpp
    Created: 24 Jan 2017 10:37:37pm
    Author:  Jordan Hochenbaum

  ==============================================================================
*/

#include "ParameterMapUI.h"

ParameterMapUI::ParameterMapUI(AudioProcessor* p_) : numRows(0)
{
    processor = static_cast<ChuckRacksAudioProcessor*>(p_);
    parameterListModel = processor->getParameterListModel();
    addAndMakeVisible(table);
    table.setRowHeight (20);
    table.setModel (this);
    
    // give it a border
    //table.setColour (ListBox::outlineColourId, Colours::black);
    //table.setOutlineThickness (1);
    table.getHeader().addColumn("#", 1, 30, TableHeaderComponent::notSortable);
    table.getHeader().addColumn("Parameter Name", 2, 280, TableHeaderComponent::notSortable);
    //table.getHeader().addColumn("Add New", 3, 60, TableHeaderComponent::notSortable);
    
    table.setColour(TableListBox::backgroundColourId, Colour(38, 40, 49));
    //addRow();
    //addRow();
    //parameterListModel.insert(std::make_pair(0, String("Cutoff")));
    /*for (int i=0; i<numRows; i++) {
        parameterListModel.insert(std::make_pair(i, String("not assigned")));
    }*/
    
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

    //g.setColour(Colour(40, 43, 34));
    //g.fillAll(Colours::black);
    //g.fillAll(Colour(40, 43, 34));
    //g.fillAll(Colours::black.withAlpha (0.8f));
}

void ParameterMapUI::resized(){
    table.setBoundsInset (BorderSize<int> (1));
    addNewButton->setBounds(getWidth()-28, 2, 26, 26);
}

void ParameterMapUI::buttonClicked (Button* buttonThatWasClicked){
    if (buttonThatWasClicked == addNewButton) {
        addRow();
    }
}

void ParameterMapUI::addRow(){
    //if (numRows+1 < 512)
    //    parameterListModel.insert(std::make_pair(numRows, String("not assigned")));
    
    //numRows++;
    processor->mapNewParam();
    table.resized();

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
   
    if (rowIsSelected)
        g.fillAll (Colours::lightslategrey);
    //else if (rowNumber % 2)
    //    g.fillAll (Colour(100, 106, 127));
    else
        g.fillAll(Colour(38, 40, 49));
        //g.fillAll(Colour(28, 30, 37));
}

// This is overloaded from TableListBoxModel, and must paint any cells that aren't using custom
// components.
void ParameterMapUI::paintCell (Graphics& g, int rowNumber, int columnId,
                int width, int height, bool /*rowIsSelected*/)
{
    g.setColour (Colours::black.withAlpha (0.2f));
    g.fillRect (width - 1, 0, 1, height);
    
    g.setFont (font);

    //std::map<int, String> pModel(processor->getParameterListModel());
    //std::cout << "painting " << rowNumber << " " << columnId << std::endl;
    if ( parameterListModel->at(rowNumber).isNotEmpty() )
    {
        //std::cout << "dfdfsdf" << std::endl;
        String text;
        if (columnId == 1){
            g.setColour (Colour(62, 172, 133));
            text = String(rowNumber);
        }
        
        else if (columnId == 2){
            g.setColour (Colours::grey);
            text = parameterListModel->at(rowNumber);
        }else{
            text = String();
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
    //std::map<int, String> pModel (processor->getParameterListModel());
    //std::cout << processor->getParameterListModel().find(rowNumber)->second << std::endl;
    return parameterListModel->find(rowNumber)->second;
    //return dataList->getChildElement (rowNumber)->getStringAttribute ( getAttributeNameForColumnId(columnNumber));
}

void ParameterMapUI::setText (const int columnNumber, const int rowNumber, const String& newText)
{
    String text = newText;

    if (text.isEmpty())
        text = "not assigned";
    //std::map<int, String> pModel (processor->getParameterListModel());

    parameterListModel->find(rowNumber)->second = text;
    processor->updateParamNames(rowNumber, text);
    table.deselectRow(rowNumber);
    //dataList->getChildElement (rowNumber)->setAttribute (columnName, newText);
}
