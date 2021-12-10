/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionPluginAudioProcessorEditor::DistortionPluginAudioProcessorEditor (DistortionPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    driveSlider.addListener(this);
    foldThreshSlider.addListener(this);
    offsetSlider.addListener(this);
    foldOutSlider.addListener(this);
    crushMixSlider.addListener(this);
    sClipInSlider.addListener(this);
    posAlphaSlider.addListener(this);
    posThreshSlider.addListener(this);
    negAlphaSlider.addListener(this);
    negThreshSlider.addListener(this);
    sClipOutSlider.addListener(this);
    clipMixSlider.addListener(this);
    wetDrySlider.addListener(this);
    outputGainSlider.addListener(this);

    symmetryToggle.addListener(this);   
    twoButton.addListener(this);
    fourButton.addListener(this);
    eightButton.addListener(this);
    sixteenButton.addListener(this);

    using sliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    driveSliderAttachment = std::make_unique<sliderAttachment>      (audioProcessor.parameterTree, "DRIVE",     driveSlider);
    foldThreshSliderAttachment = std::make_unique<sliderAttachment> (audioProcessor.parameterTree, "FOLDTHR",   foldThreshSlider);
    offsetSliderAttachment = std::make_unique<sliderAttachment>     (audioProcessor.parameterTree, "OFFSET",    offsetSlider);
    foldOutSliderAttachment = std::make_unique<sliderAttachment>    (audioProcessor.parameterTree, "FOUT",      foldOutSlider);
    crushMixSliderAttachment = std::make_unique<sliderAttachment>   (audioProcessor.parameterTree, "CRMIX",     crushMixSlider);
    sClipInSliderAttachment = std::make_unique<sliderAttachment>    (audioProcessor.parameterTree, "CLIPIN",    sClipInSlider);
    posAlphaSliderAttachment = std::make_unique<sliderAttachment>   (audioProcessor.parameterTree, "PALPH",     posAlphaSlider);
    posThreshSliderAttachment = std::make_unique<sliderAttachment>  (audioProcessor.parameterTree, "PTHR",      posThreshSlider);
    negAlphaSliderAttachment = std::make_unique<sliderAttachment>   (audioProcessor.parameterTree, "NALPH",     negAlphaSlider);
    negThreshSliderAttachment = std::make_unique<sliderAttachment>  (audioProcessor.parameterTree, "NTHR",      negThreshSlider);
    sClipOutSliderAttachment = std::make_unique<sliderAttachment>   (audioProcessor.parameterTree, "CLIPOUT",   sClipOutSlider);
    clipMixSliderAttachment = std::make_unique<sliderAttachment>    (audioProcessor.parameterTree, "MIX",       clipMixSlider);
    wetDrySliderAttachment = std::make_unique<sliderAttachment>     (audioProcessor.parameterTree, "WDMIX",     wetDrySlider);
    outputGainSliderAttachment = std::make_unique<sliderAttachment> (audioProcessor.parameterTree, "OUT",       outputGainSlider);
    symmetryToggleAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.parameterTree, "SYM", symmetryToggle);        
    
    setSlider(driveSlider, 0.0f, 3.0f, 0.01f, 1.0f);
    setLabel(driveLabel, driveSlider, "Drive");
     
    setSlider(foldThreshSlider, 0.05f, 1.0f, 0.01f, 1.0f);
    setLabel(foldThreshLabel, foldThreshSlider, "Thresh");

    setSlider(offsetSlider, -0.5f, 0.5f, 0.01f, 0.0f);
    setLabel(offsetLabel, offsetSlider, "Bias");    
       
    setSlider(foldOutSlider, 0.0f, 3.0f, 0.01f, 1.0f);
    setLabel(foldOutLabel, foldOutSlider, "Level");
        
    setSlider(crushMixSlider, 0.0f, 1.0f, 0.01f, 0.5f);
    setLabel(crushMixLabel, crushMixSlider, "Mix");
        
    setSlider(sClipInSlider, 0.0f, 2.5f, 0.01f, 1.0f);
    setLabel(sClipInLabel, sClipInSlider, "Drive");
       
    setSlider(posAlphaSlider, 0.1f, 20.0f, 0.1f, 1.0f);
    setLabel(posAlphaLabel, posAlphaSlider, "(+) Alpha");
        
    setSlider(posThreshSlider, 0.0f, 1.0f, 0.01f, 1.0f);
    setLabel(posThreshLabel, posThreshSlider, "(+) Thresh");

    setSlider(negAlphaSlider, 0.1f, 20.0f, 0.1f, 1.0f);
    setLabel(negAlphaLabel, negAlphaSlider, "(-) Alpha");

    setSlider(negThreshSlider, -1.0f, 1.0f, 0.01f, 1.0f);
    setLabel(negThreshLabel, negThreshSlider, "(-) Thresh");

    setSlider(sClipOutSlider, 0.0f, 1.5f, 0.01f, 1.0f);
    setLabel(sClipOutLabel, sClipOutSlider, "Level");

    setSlider(clipMixSlider, 0.0f, 1.0f, 0.01f, 0.5f, juce::Colours::silver, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    setLabel(clipMixLabel, clipMixSlider, "Mix");

    setSlider(wetDrySlider, 0.0f, 1.0f, 0.01f, 1.0f, juce::Colours::silver, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    setLabel(wetDryLabel, wetDrySlider, "Wet/Dry Mix");

    setSlider(outputGainSlider, 0.0f, 1.3f, 0.01f, 1.0f, juce::Colours::silver, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    setLabel(outputGainLabel, outputGainSlider, "Output");

    setButton(symmetryToggle);
    setLabel(symmetryLabel, symmetryToggle, "Symmetry", false);

    setButton(twoButton);
    setButton(fourButton);
    setButton(eightButton);
    setButton(sixteenButton);
    setLabel(stepsLabel, twoButton, "Steps", false);
    
    setTitle(folderLabel, "Wave Folder");
    setTitle(clipperLabel, "Soft Clipper");
    setTitle(crusherLabel, "Bit Crusher");
    setTitle(utilitiesLabel, "Output");

    setSize (505, 430);
}

DistortionPluginAudioProcessorEditor::~DistortionPluginAudioProcessorEditor()
{
}

//==============================================================================
void DistortionPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::darkslategrey);
    g.setColour(juce::Colours::whitesmoke);
    g.drawRoundedRectangle(15.0f,   35.0f,  210.0f, 170.0f, 3.0f, 1.0f); //Wave folder
    g.drawRoundedRectangle(15.0f,   225.0f, 360.0f, 170.0f, 3.0f, 1.0f); //Soft Clipper
    g.drawRoundedRectangle(240.0f,  35.0f,  135.0f, 170.0f, 3.0f, 1.0f); //Bit Crusher
    g.drawRoundedRectangle(390.0f,  35.0f,  100.0f, 360.0f, 3.0f, 1.0f); //Output
}

void DistortionPluginAudioProcessorEditor::resized()
{
    int row2y = 260, row1y = 70, slHeight = 120, slWidth = 50;
    driveSlider.setBounds       (20,  row1y, slWidth, slHeight);
    foldThreshSlider.setBounds  (70,  row1y, slWidth, slHeight);
    offsetSlider.setBounds      (120, row1y, slWidth, slHeight);
    foldOutSlider.setBounds     (170, row1y, slWidth, slHeight);
    crushMixSlider.setBounds    (320, row1y, slWidth, slHeight);

    sClipInSlider.setBounds     (20,  row2y, slWidth, slHeight);
    posAlphaSlider.setBounds    (70,  row2y, slWidth, slHeight);
    posThreshSlider.setBounds   (120, row2y, slWidth, slHeight);

    negAlphaSlider.setBounds    (220, row2y, slWidth, slHeight);
    negThreshSlider.setBounds   (270, row2y, slWidth, slHeight);
    sClipOutSlider.setBounds    (320, row2y, slWidth, slHeight);

    clipMixSlider.setBounds     (400, row1y,       80, 80);
    wetDrySlider.setBounds      (400, row1y + 110, 80, 80);
    outputGainSlider.setBounds  (400, row1y + 220, 80, 80);
    
    symmetryToggle.setBounds    (182, row2y + 30, 50, 50);
    symmetryLabel.setBounds     (165, row2y , 60, 30);    
    twoButton.setBounds         (260, row1y + 20, 30, 30);
    fourButton.setBounds        (290, row1y + 20, 30, 30);
    eightButton.setBounds       (260, row1y + 50, 30, 30);
    sixteenButton.setBounds     (290, row1y + 50, 30, 30);
    stepsLabel.setBounds        (270, row1y - 25, 40, 30);

    folderLabel.setBounds       (25, row1y - 50,  110, 30);
    clipperLabel.setBounds      (25, row2y - 50,  110, 30);
    crusherLabel.setBounds      (250, row1y - 50, 100, 30);
    utilitiesLabel.setBounds    (400, row1y - 50, 70,  30);
}

void DistortionPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) 
{
    if (slider == &driveSlider) 
    {
        audioProcessor.driveCurrent = *audioProcessor.parameterTree.getRawParameterValue("DRIVE");
    }
    else if (slider == &foldThreshSlider) 
    {
        audioProcessor.foldThreshCurrent = *audioProcessor.parameterTree.getRawParameterValue("FOLDTHR");
    }
    else if (slider == &foldOutSlider)
    {
        audioProcessor.fOutCurrent = *audioProcessor.parameterTree.getRawParameterValue("FOUT");
    }
    else if (slider == &crushMixSlider)
    {
        audioProcessor.crMixCurrent = *audioProcessor.parameterTree.getRawParameterValue("CRMIX");
    }
    else if (slider == &sClipInSlider)
    {
        audioProcessor.clipInCurrent = *audioProcessor.parameterTree.getRawParameterValue("CLIPIN");
    }
    else if (slider == &posAlphaSlider)
    {
        audioProcessor.posAlphCurrent = *audioProcessor.parameterTree.getRawParameterValue("PALPH");
        if(audioProcessor.distortion.getSymmetryToggle() == true)
            audioProcessor.negAlphCurrent = *audioProcessor.parameterTree.getRawParameterValue("PALPH");
    }
    else if (slider == &posThreshSlider)
    {
        audioProcessor.posThreshCurrent = *audioProcessor.parameterTree.getRawParameterValue("PTHR");
        if (audioProcessor.distortion.getSymmetryToggle() == true)
            audioProcessor.negThreshCurrent = *audioProcessor.parameterTree.getRawParameterValue("PTHR");
    }
    else if (slider == &negAlphaSlider)
    {
        audioProcessor.negAlphCurrent = *audioProcessor.parameterTree.getRawParameterValue("NALPH");
    }
    else if (slider == &negThreshSlider)
    {
        audioProcessor.negThreshCurrent = *audioProcessor.parameterTree.getRawParameterValue("NTHR");
    }
    else if (slider == &sClipOutSlider)
    {
        audioProcessor.clipOutCurrent = *audioProcessor.parameterTree.getRawParameterValue("CLIPOUT");
    }
    else if (slider == &clipMixSlider)
    {
        audioProcessor.mixCurrent = *audioProcessor.parameterTree.getRawParameterValue("MIX");
    }
    else if (slider == &wetDrySlider)
    {
        audioProcessor.wetDryCurrent = *audioProcessor.parameterTree.getRawParameterValue("WDMIX");
    }
    else if (slider == &outputGainSlider)
    {
        audioProcessor.outputGainCurrent = *audioProcessor.parameterTree.getRawParameterValue("OUT");
    }
}

void DistortionPluginAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &symmetryToggle)
    {
        audioProcessor.distortion.setSymmetryToggle(*audioProcessor.parameterTree.getRawParameterValue("SYM"));
        if (audioProcessor.distortion.getSymmetryToggle() == true)
        {
            audioProcessor.negAlphCurrent = *audioProcessor.parameterTree.getRawParameterValue("PALPH");
            audioProcessor.negThreshCurrent = *audioProcessor.parameterTree.getRawParameterValue("PTHR");
            negThreshSlider.setVisible(false);
            negAlphaSlider.setVisible(false);
        }
        else 
        {
            audioProcessor.negAlphCurrent = *audioProcessor.parameterTree.getRawParameterValue("NALPH");
            audioProcessor.negThreshCurrent = *audioProcessor.parameterTree.getRawParameterValue("NTHR");
            negThreshSlider.setVisible(true);
            negAlphaSlider.setVisible(true);
        }
    }
    else if (button == &twoButton)
    {
        audioProcessor.distortion.setCrushSteps(2);
    }
    else if (button == &fourButton)
    {
        audioProcessor.distortion.setCrushSteps(4);
    }
    else if (button == &eightButton)
    {
        audioProcessor.distortion.setCrushSteps(8);
    }
    else if (button == &sixteenButton)
    {
        audioProcessor.distortion.setCrushSteps(16);
    }
}

void DistortionPluginAudioProcessorEditor::setSlider(juce::Slider& slider, float min, float max, float step, float default, juce::Colour colour, juce::Slider::SliderStyle style)
{
    addAndMakeVisible(slider);    
    slider.setSliderStyle(style);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 40, 15);
    slider.setRange(min, max, step);
    slider.setValue(default);
    slider.setColour(juce::Slider::thumbColourId, colour);
    slider.setColour(juce::Slider::backgroundColourId, juce::Colours::black);
    slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::black);
    slider.setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    slider.setColour(juce::Slider::trackColourId, juce::Colours::black);

}

void DistortionPluginAudioProcessorEditor::setLabel(juce::Label& label, juce::Component& component, std::string name, bool attach)
{
    
    if (attach == true) label.attachToComponent(&component, false);
    label.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(12);
    addAndMakeVisible(label);
}

void DistortionPluginAudioProcessorEditor::setTitle(juce::Label& label, std::string name)
{
    label.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    label.setColour(juce::Label::backgroundColourId, juce::Colours::darkslategrey);
    label.setText(name, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(20);
    label.setColour(juce::Label::outlineColourId, juce::Colours::whitesmoke);
    addAndMakeVisible(label);
}

void DistortionPluginAudioProcessorEditor::setButton(juce::Button& button)
{
    button.setColour(juce::TextButton::buttonColourId, juce::Colours::darkslategrey);
    addAndMakeVisible(button);
}

