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
    symmetryToggle.setToggleState(false, juce::dontSendNotification);
    addAndMakeVisible(symmetryToggle);
    symmetryLabel.setText("SYMMETRY", juce::dontSendNotification);
    symmetryLabel.attachToComponent(&symmetryToggle, false);
    addAndMakeVisible(symmetryLabel);

    
    
    twoButton.addListener(this);
    fourButton.addListener(this);
    eightButton.addListener(this);
    sixteenButton.addListener(this); 
    addAndMakeVisible(twoButton);
    addAndMakeVisible(fourButton);
    addAndMakeVisible(eightButton);
    addAndMakeVisible(sixteenButton);



    driveSlider.addListener(this);
    foldsSlider.addListener(this);
    offsetSlider.addListener(this);
    foldOutSlider.addListener(this);
    crushStepsSlider.addListener(this);
    crushMixSlider.addListener(this);
    sClipInSlider.addListener(this);
    posAlphaSlider.addListener(this);
    posThreshSlider.addListener(this);
    negAlphaSlider.addListener(this);
    negThreshSlider.addListener(this);
    sClipOutSlider.addListener(this);
    clipMixSlider.addListener(this);

    driveSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "DRIVE", driveSlider);
    setSlider(driveSlider, 0.0f, 3.0f, 0.01f, 1.0f, juce::Colours::orange);
    setLabel(driveLabel, driveSlider, "DRIVE");

    
    foldsSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "FOLDS", foldsSlider);
    setSlider(foldsSlider, 0.0f, 1.0f, 0.01f, 1.0f, juce::Colours::orange);
    setLabel(foldsLabel, foldsSlider, "FOLD THRESH");

    
    offsetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "OFFSET", offsetSlider);
    setSlider(offsetSlider, -0.5f, 0.5f, 0.01f, 0.0f, juce::Colours::orange);
    setLabel(offsetLabel, offsetSlider, "OFFSET");



    
    foldOutSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "FOUT", foldOutSlider);
    setSlider(foldOutSlider, 0.0f, 3.0f, 0.01f, 1.0f, juce::Colours::orange);
    setLabel(foldOutLabel, foldOutSlider, "OUTPUT GAIN");

    
    crushStepsSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "STEPS", crushStepsSlider);
    setSlider(crushStepsSlider, 4.0f, 16.0f, 4.0f, 16.0f, juce::Colours::purple);
    setLabel(stepsLabel, crushStepsSlider, "CRUSH STEPS");


    
    crushMixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "CRMIX", crushMixSlider);
    setSlider(crushMixSlider, 0.0f, 1.0f, 0.01f, 0.5f, juce::Colours::purple);
    setLabel(crushMixLabel, crushMixSlider, "CRUSH MIX");

    
    sClipInSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "CLIPIN", sClipInSlider);
    setSlider(sClipInSlider, 0.0f, 1.5f, 0.01f, 1.0f, juce::Colours::firebrick);
    setLabel(sClipInLabel, sClipInSlider, "DRIVE");

    
    posAlphaSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "PALPH", posAlphaSlider);
    setSlider(posAlphaSlider, 0.1f, 20.0f, 0.1f, 1.0f, juce::Colours::firebrick);
    setLabel(posAlphaLabel, posAlphaSlider, "POS ALPHA");

    
    posThreshSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "PTHR", posThreshSlider);
    setSlider(posThreshSlider, 0.0f, 1.0f, 0.01f, 1.0f, juce::Colours::firebrick);
    setLabel(posThreshLabel, posThreshSlider, "POS THRESHOLD");


    negAlphaSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "NALPH", negAlphaSlider);
    setSlider(negAlphaSlider, 0.1f, 20.0f, 0.1f, 1.0f, juce::Colours::firebrick);
    setLabel(negAlphaLabel, negAlphaSlider, "NEG ALPHA");

    negThreshSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "NTHR", negThreshSlider);
    setSlider(negThreshSlider, -1.0f, 1.0f, 0.01f, 1.0f, juce::Colours::firebrick);
    setLabel(negThreshLabel, negThreshSlider, "NEG THRESHOLD");

    sClipOutSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "CLIPOUT", sClipOutSlider);
    setSlider(sClipOutSlider, 0.0f, 1.5f, 0.01f, 1.0f, juce::Colours::firebrick);
    setLabel(sClipOutLabel, sClipOutSlider, "OUTPUT GAIN");

    clipMixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "MIX", clipMixSlider);
    setSlider(clipMixSlider, 0.0f, 1.0f, 0.01f, 0.5f, juce::Colours::sandybrown);
    setLabel(clipMixLabel, clipMixSlider, "MIX");
    
    
    
    setSize (900, 350);
}

DistortionPluginAudioProcessorEditor::~DistortionPluginAudioProcessorEditor()
{
}

//==============================================================================
void DistortionPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::slategrey);

}

void DistortionPluginAudioProcessorEditor::resized()
{
    driveSlider.setBounds       (20,  40, 100, 100);
    foldsSlider.setBounds       (120, 40, 100, 100);
    offsetSlider.setBounds      (220, 40, 100, 100);
    foldOutSlider.setBounds     (320, 40, 100, 100);
    //crushStepsSlider.setBounds  (520, 40, 100, 100);
    crushMixSlider.setBounds    (620, 40, 100, 100);
    sClipInSlider.setBounds     (20,  200, 100, 100);
    posAlphaSlider.setBounds    (120, 200, 100, 100);
    posThreshSlider.setBounds   (220, 200, 100, 100);
    symmetryToggle.setBounds    (350, 200, 50, 50);
    negAlphaSlider.setBounds    (420, 200, 100, 100);
    negThreshSlider.setBounds   (520, 200, 100, 100);
    sClipOutSlider.setBounds    (620, 200, 100, 100);
    clipMixSlider.setBounds     (750, 40, 40, 260);

    twoButton.setBounds(520, 40, 40, 40);
    fourButton.setBounds(560, 40, 40, 40);
    eightButton.setBounds(520, 80, 40, 40);
    sixteenButton.setBounds(560, 80, 40, 40);

}

void DistortionPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) 
{
    /*if (slider == &driveSlider) {
        audioProcessor.distortion.setFoldDrive(*audioProcessor.parameterTree.getRawParameterValue("DRIVE"));
        
    }
    */if (slider == &foldsSlider) {
        audioProcessor.distortion.setFoldThresh(*audioProcessor.parameterTree.getRawParameterValue("FOLDS"));
        
    }/*
    else if (slider == &offsetSlider){
        audioProcessor.distortion.setFoldOffset(*audioProcessor.parameterTree.getRawParameterValue("OFFSET"));
        
}
    else if (slider == &foldOutSlider){
        audioProcessor.distortion.setFoldOutGain(*audioProcessor.parameterTree.getRawParameterValue("FOUT"));
        
    }*/
    else if (slider == &crushStepsSlider) {
        audioProcessor.distortion.setCrushSteps(*audioProcessor.parameterTree.getRawParameterValue("STEPS"));
        
    }/*
    else if (slider == &crushMixSlider)
    {
        audioProcessor.distortion.setCrushMix(*audioProcessor.parameterTree.getRawParameterValue("CRMIX"));
    }
    else if (slider == &sClipInSlider)
    {
        audioProcessor.distortion.setSClipInGain(*audioProcessor.parameterTree.getRawParameterValue("CLIPIN"));
    }
    else if (slider == &posAlphaSlider)
    {
        audioProcessor.distortion.setPosAlpha(*audioProcessor.parameterTree.getRawParameterValue("PALPH"));
    }
    else if (slider == &posThreshSlider)
    {
        audioProcessor.distortion.setSClipPosThresh(*audioProcessor.parameterTree.getRawParameterValue("PTHR"));
    }
    else if (slider == &negAlphaSlider)
    {
        audioProcessor.distortion.setNegAlpha(*audioProcessor.parameterTree.getRawParameterValue("NALPH"));
    }
    else if (slider == &negThreshSlider)
    {
        audioProcessor.distortion.setSClipNegThresh(*audioProcessor.parameterTree.getRawParameterValue("NTHR"));
    }
    else if (slider == &sClipOutSlider)
    {
        audioProcessor.distortion.setSClipOutGain(*audioProcessor.parameterTree.getRawParameterValue("CLIPOUT"));
    }
    else if (slider == &clipMixSlider)
    {
        audioProcessor.distortion.setMix(*audioProcessor.parameterTree.getRawParameterValue("MIX"));
    }
    */
}

void DistortionPluginAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &symmetryToggle)
    {
        audioProcessor.distortion.setSymmetryToggle(*audioProcessor.parameterTree.getRawParameterValue("SYM"));
        if (audioProcessor.distortion.getSymmetryToggle() == true)
        {
            audioProcessor.distortion.setPosAlpha(*audioProcessor.parameterTree.getRawParameterValue("PALPH"));
            audioProcessor.distortion.setSClipPosThresh(*audioProcessor.parameterTree.getRawParameterValue("PTHR"));
            negThreshSlider.setVisible(false);
            negAlphaSlider.setVisible(false);
        }
        else 
        {
            audioProcessor.distortion.setNegAlpha(*audioProcessor.parameterTree.getRawParameterValue("NALPH"));
            audioProcessor.distortion.setSClipNegThresh(*audioProcessor.parameterTree.getRawParameterValue("NTHR"));
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

void DistortionPluginAudioProcessorEditor::setSlider(juce::Slider& slider, float min, float max, float step, float default, juce::Colour colour)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 30);
    slider.setRange(min, max, step);
    slider.setColour(juce::Slider::thumbColourId, colour);
    slider.setColour(juce::Slider::backgroundColourId, juce::Colours::black);
    slider.setColour(juce::Slider::trackColourId, juce::Colours::black);
    addAndMakeVisible(slider);
}

void DistortionPluginAudioProcessorEditor::setLabel(juce::Label& label, juce::Slider& slider, std::string name) 
{
    label.setColour(juce::Label::textColourId, juce::Colours::white);
    label.setText(name, juce::dontSendNotification);
    label.attachToComponent(&slider, false);
    addAndMakeVisible(label);
}

//void DistortionPluginAudioProcessorEditor::setButton(juce::Label& label, juce::Slider& slider, std::string name)
