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
    symmetryToggle.addListener(this);   
    symmetryToggleAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.parameterTree, "SYM", symmetryToggle);

       
    symmetryToggle.setClickingTogglesState(true);
    symmetryToggle.setToggleState(false, juce::dontSendNotification); 
    addAndMakeVisible(symmetryToggle);

    setLabel(symmetryLabel, symmetryToggle, "Symmetry", false);
    setLabel(stepsLabel, twoButton, "Steps", false);


    
    twoButton.addListener(this);
    fourButton.addListener(this);
    eightButton.addListener(this);
    sixteenButton.addListener(this);
    twoButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkslategrey);
    fourButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkslategrey);
    eightButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkslategrey);
    sixteenButton.setColour(juce::TextButton::buttonColourId, juce::Colours::darkslategrey);
    addAndMakeVisible(twoButton);
    addAndMakeVisible(fourButton);
    addAndMakeVisible(eightButton);
    addAndMakeVisible(sixteenButton);




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



    driveSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "DRIVE", driveSlider);
    setSlider(driveSlider, 0.0f, 3.0f, 0.01f, 1.0f);
    setLabel(driveLabel, driveSlider, "Drive");

    
    foldThreshSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "FOLDTHR", foldThreshSlider);
    setSlider(foldThreshSlider, 0.05f, 1.0f, 0.01f, 1.0f);
    setLabel(foldThreshLabel, foldThreshSlider, "Thresh");

    offsetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "OFFSET", offsetSlider);    
    setSlider(offsetSlider, -0.5f, 0.5f, 0.01f, 0.0f);
    setLabel(offsetLabel, offsetSlider, "Bias");    



    
    foldOutSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "FOUT", foldOutSlider);
    setSlider(foldOutSlider, 0.0f, 3.0f, 0.01f, 1.0f);
    setLabel(foldOutLabel, foldOutSlider, "Gain");


    
    crushMixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "CRMIX", crushMixSlider);
    setSlider(crushMixSlider, 0.0f, 1.0f, 0.01f, 0.5f);
    setLabel(crushMixLabel, crushMixSlider, "Mix");

    
    sClipInSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "CLIPIN", sClipInSlider);
    setSlider(sClipInSlider, 0.0f, 1.5f, 0.01f, 1.0f);
    setLabel(sClipInLabel, sClipInSlider, "Drive");

    
    posAlphaSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "PALPH", posAlphaSlider);
    setSlider(posAlphaSlider, 0.1f, 20.0f, 0.1f, 1.0f);
    setLabel(posAlphaLabel, posAlphaSlider, "(+) Alpha");

    
    posThreshSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "PTHR", posThreshSlider);
    setSlider(posThreshSlider, 0.0f, 1.0f, 0.01f, 1.0f);
    setLabel(posThreshLabel, posThreshSlider, "(+) Thresh");


    negAlphaSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "NALPH", negAlphaSlider);
    setSlider(negAlphaSlider, 0.1f, 20.0f, 0.1f, 1.0f);
    setLabel(negAlphaLabel, negAlphaSlider, "(-) Alpha");

    negThreshSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "NTHR", negThreshSlider);
    setSlider(negThreshSlider, -1.0f, 1.0f, 0.01f, 1.0f);
    setLabel(negThreshLabel, negThreshSlider, "(-) Thresh");

    sClipOutSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "CLIPOUT", sClipOutSlider);
    setSlider(sClipOutSlider, 0.0f, 1.5f, 0.01f, 1.0f);
    setLabel(sClipOutLabel, sClipOutSlider, "Gain");

    clipMixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "MIX", clipMixSlider);
    setSlider(clipMixSlider, 0.0f, 1.0f, 0.01f, 0.5f, juce::Colours::silver, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    setLabel(clipMixLabel, clipMixSlider, "Mix");

    wetDrySliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "WDMIX", wetDrySlider);
    setSlider(wetDrySlider, 0.0f, 1.0f, 0.01f, 1.0f, juce::Colours::silver, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    setLabel(wetDryLabel, wetDrySlider, "Wet/Dry Mix");

    outputGainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "OUT", outputGainSlider);
    setSlider(outputGainSlider, 0.0f, 1.3f, 0.01f, 1.0f, juce::Colours::silver, juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    setLabel(outputGainLabel, outputGainSlider, "Output");
    
    folderLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    folderLabel.setColour(juce::Label::backgroundColourId , juce::Colours::darkslategrey);
    folderLabel.setText("Wave Folder", juce::dontSendNotification);
    folderLabel.setJustificationType(juce::Justification::centred);
    folderLabel.setFont(20);
    folderLabel.setColour(juce::Label::outlineColourId, juce::Colours::whitesmoke);
    addAndMakeVisible(folderLabel);

    clipperLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    clipperLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkslategrey);
    clipperLabel.setColour(juce::Label::outlineColourId, juce::Colours::whitesmoke);
    clipperLabel.setText("Soft Clipper", juce::dontSendNotification);
    clipperLabel.setJustificationType(juce::Justification::centred);
    clipperLabel.setFont(20);
    addAndMakeVisible(clipperLabel);
    
    crusherLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    crusherLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkslategrey);
    crusherLabel.setColour(juce::Label::outlineColourId, juce::Colours::whitesmoke);
    crusherLabel.setText("Bit Crusher", juce::dontSendNotification);
    crusherLabel.setJustificationType(juce::Justification::centred);
    crusherLabel.setFont(20);
    addAndMakeVisible(crusherLabel);

    utilitiesLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    utilitiesLabel.setColour(juce::Label::backgroundColourId, juce::Colours::darkslategrey);
    utilitiesLabel.setColour(juce::Label::outlineColourId, juce::Colours::whitesmoke);
    utilitiesLabel.setText("Output", juce::dontSendNotification);
    utilitiesLabel.setJustificationType(juce::Justification::centred);
    utilitiesLabel.setFont(20);
    addAndMakeVisible(utilitiesLabel);

    setSize (505, 430);
}

DistortionPluginAudioProcessorEditor::~DistortionPluginAudioProcessorEditor()
{
}

//==============================================================================
void DistortionPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::darkslategrey);
    g.setColour(juce::Colours::whitesmoke);
    g.drawRoundedRectangle(15.0f, 35.0f, 210.0f, 170.0f, 3.0f, 1.0f);
    g.drawRoundedRectangle(15.0f, 225.0f, 360.0f, 170.0f, 3.0f, 1.0f);
    g.drawRoundedRectangle(240.0f, 35.0f, 135.0f, 170.0f, 3.0f, 1.0f);
    g.drawRoundedRectangle(390.0f, 35.0f, 100.0f, 360.0f, 3.0f, 1.0f);

}

void DistortionPluginAudioProcessorEditor::resized()
{
    int row2y = 260, row1y = 70;
    driveSlider.setBounds       (20, row1y, 50,  120);
    foldThreshSlider.setBounds  (70, row1y, 50,  120);
    offsetSlider.setBounds      (120, row1y, 50, 120);
    foldOutSlider.setBounds     (170, row1y, 50, 120);


    crushMixSlider.setBounds    (320, row1y, 50, 120);

    sClipInSlider.setBounds     (20, row2y, 50,  120);
    posAlphaSlider.setBounds    (70, row2y, 50,  120);
    posThreshSlider.setBounds   (120, row2y, 50, 120);
    symmetryToggle.setBounds    (182, row2y + 30, 50, 50);
    negAlphaSlider.setBounds    (220, row2y, 50, 120);
    negThreshSlider.setBounds   (270, row2y, 50, 120);
    sClipOutSlider.setBounds    (320, row2y, 50, 120);

    clipMixSlider.setBounds     (400, row1y, 80, 80);
    wetDrySlider.setBounds(400, row1y + 110, 80, 80);
    outputGainSlider.setBounds(400, row1y + 220, 80, 80);


    twoButton.setBounds         (260, row1y + 20, 30, 30);
    fourButton.setBounds        (290, row1y + 20, 30, 30);
    eightButton.setBounds       (260, row1y + 50, 30, 30);
    sixteenButton.setBounds     (290, row1y + 50, 30, 30);

    folderLabel.setBounds       (25, row1y - 50, 110, 30);
    clipperLabel.setBounds      (25, row2y - 50, 110, 30);
    crusherLabel.setBounds      (250, row1y - 50, 100, 30);
    utilitiesLabel.setBounds(400, row1y - 50, 70, 30);

    stepsLabel.setBounds        (270, row1y - 25, 40, 30);
    symmetryLabel.setBounds     (165, row2y , 60, 30);
}

void DistortionPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) 
{
    if (slider == &driveSlider) 
    {
        audioProcessor.driveCurrent = *audioProcessor.parameterTree.getRawParameterValue("DRIVE");
    }
    else if (slider == &foldThreshSlider) 
    {
        audioProcessor.distortion.setFoldThresh(*audioProcessor.parameterTree.getRawParameterValue("FOLDTHR"));
    }
    /*else if (slider == &offsetSlider)
    {
        audioProcessor.offsetCurrent = *audioProcessor.parameterTree.getRawParameterValue("OFFSET");
    }*/
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
    }
    else if (slider == &posThreshSlider)
    {
        audioProcessor.posThreshCurrent = *audioProcessor.parameterTree.getRawParameterValue("PTHR");
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

//void DistortionPluginAudioProcessorEditor::setButton(juce::Label& label, juce::Slider& slider, std::string name)
