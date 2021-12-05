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
    
    driveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    driveSlider.addListener(this);
    driveSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "DRIVE", driveSlider);
    driveSlider.setRange(0.0f, 5.0f, 0.01f);
    driveSlider.setValue(1.0f);
    addAndMakeVisible(driveSlider);

    
    foldsSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    foldsSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    foldsSlider.addListener(this);
    foldsSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "FOLDS", foldsSlider);
    foldsSlider.setRange(1.0f, 8.0f, 1.0f);
    foldsSlider.setValue(1.0f);
    addAndMakeVisible(foldsSlider);

    
    offsetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    offsetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    offsetSlider.addListener(this);
    offsetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "OFFSET", offsetSlider);
    offsetSlider.setRange(-0.75f, 0.75f, 0.01f);
    offsetSlider.setValue(0.0f);
    addAndMakeVisible(offsetSlider);

    
    foldOutSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    foldOutSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    foldOutSlider.addListener(this);
    foldOutSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "FOUT", foldOutSlider);
    foldOutSlider.setRange(0.0f, 5.0f, 0.01f);
    foldOutSlider.setValue(1.0f);
    addAndMakeVisible(foldOutSlider);
    
    
    crushStepsSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    crushStepsSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    crushStepsSlider.addListener(this);
    crushStepsSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "STEPS", crushStepsSlider);
    crushStepsSlider.setRange(4.0f, 16.0f, 4.0f);
    crushStepsSlider.setValue(4.0f);
    addAndMakeVisible(crushStepsSlider);

    bypassToggle.addListener(this);
    bypassToggleAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.parameterTree, "BYPASS", bypassToggle);
    bypassToggle.setToggleState(false, juce::dontSendNotification);
    addAndMakeVisible(bypassToggle);

    crushMixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    crushMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    crushMixSlider.addListener(this);
    crushMixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "CRMIX", crushMixSlider);
    crushMixSlider.setRange(0.0f, 1.0f, 0.01f);
    crushMixSlider.setValue(0.5f);
    addAndMakeVisible(crushMixSlider);
    
    sClipInSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sClipInSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    sClipInSlider.addListener(this);
    sClipInSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "CLIPIN", sClipInSlider);
    sClipInSlider.setRange(0.0f, 1.5f, 0.01f);
    sClipInSlider.setValue(1.0f);
    addAndMakeVisible(sClipInSlider);

    posAlphaSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    posAlphaSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    posAlphaSlider.addListener(this);
    posAlphaSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "PALPH", posAlphaSlider);
    posAlphaSlider.setRange(0.1f, 20.0f, 0.01f);
    posAlphaSlider.setValue(1.0f);
    addAndMakeVisible(posAlphaSlider);

    posThreshSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    posThreshSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    posThreshSlider.addListener(this);
    posThreshSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "PTHR", posThreshSlider);
    posThreshSlider.setRange(0.0f, 1.0f, 0.01f);
    posThreshSlider.setValue(1.0f);
    addAndMakeVisible(posThreshSlider);

    negAlphaSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    negAlphaSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    negAlphaSlider.addListener(this);
    negAlphaSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "NALPH", negAlphaSlider);
    negAlphaSlider.setRange(-20.0f, -0.1f, 0.01f);
    negAlphaSlider.setValue(-1.0f);
    addAndMakeVisible(negAlphaSlider);

    negThreshSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    negThreshSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    negThreshSlider.addListener(this);
    negThreshSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "NTHR", negThreshSlider);
    negThreshSlider.setRange(-1.0f, 0.0f, 0.01f);
    negThreshSlider.setValue(-1.0f);
    addAndMakeVisible(negThreshSlider);

    sClipOutSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sClipOutSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    sClipOutSlider.addListener(this);
    sClipOutSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "CLIPOUT", sClipOutSlider);
    sClipOutSlider.setRange(0.0f, 1.5f, 0.01f);
    sClipOutSlider.setValue(1.0f);
    addAndMakeVisible(sClipOutSlider);
    
    
    
    
    
    
    testSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    testSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    testSlider.setRange(-1.0f, 16.0f, 0.01f);
    testSlider.setValue(0.0f);
    addAndMakeVisible(testSlider);
    setSize (900, 500);
}

DistortionPluginAudioProcessorEditor::~DistortionPluginAudioProcessorEditor()
{
}

//==============================================================================
void DistortionPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::blue);

}

void DistortionPluginAudioProcessorEditor::resized()
{
    driveSlider.setBounds       (20, 10, 150, 150);
    foldsSlider.setBounds       (120, 10, 150, 150);
    offsetSlider.setBounds      (220, 10, 150, 150);
    foldOutSlider.setBounds     (320, 10, 150, 150);
    crushStepsSlider.setBounds  (440, 10, 150, 150);
    //testSlider.setBounds        (100, 200, 300, 50);
    bypassToggle.setBounds      (600, 10, 150, 150);
    crushMixSlider.setBounds    (650, 10, 150, 150);

    sClipInSlider.setBounds     (20,  200, 150, 150);
    posAlphaSlider.setBounds    (120, 200, 150, 150);
    posThreshSlider.setBounds   (220, 200, 150, 150);
    negAlphaSlider.setBounds    (320, 200, 150, 150);
    negThreshSlider.setBounds   (420, 200, 150, 150);
    sClipOutSlider.setBounds    (520, 200, 150, 150);

}

void DistortionPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) 
{
    if (slider == &driveSlider) {
        audioProcessor.distortion.setFoldDrive(*audioProcessor.parameterTree.getRawParameterValue("DRIVE"));
        testSlider.setValue(*audioProcessor.parameterTree.getRawParameterValue("DRIVE"));
    }
    else if (slider == &foldsSlider) {
        audioProcessor.distortion.setFolds(*audioProcessor.parameterTree.getRawParameterValue("FOLDS"));
        testSlider.setValue(audioProcessor.distortion.getFolds());
    }
    else if (slider == &offsetSlider){
        audioProcessor.distortion.setFoldOffset(*audioProcessor.parameterTree.getRawParameterValue("OFFSET"));
        testSlider.setValue(*audioProcessor.parameterTree.getRawParameterValue("OFFSET"));
}
    else if (slider == &foldOutSlider){
        audioProcessor.distortion.setFoldOutGain(*audioProcessor.parameterTree.getRawParameterValue("FOUT"));
        testSlider.setValue(*audioProcessor.parameterTree.getRawParameterValue("FOUT"));
    }
    else if (slider == &crushStepsSlider) {
        audioProcessor.distortion.setCrushSteps(*audioProcessor.parameterTree.getRawParameterValue("STEPS"));
        testSlider.setValue(*audioProcessor.parameterTree.getRawParameterValue("STEPS"));
    }
    else if (slider == &crushMixSlider)
    {
        audioProcessor.distortion.setCrushAmt(*audioProcessor.parameterTree.getRawParameterValue("CRMIX"));
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
    
}

void DistortionPluginAudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &bypassToggle)
    {
        audioProcessor.distortion.setCrushBypass(*audioProcessor.parameterTree.getRawParameterValue("BYPASS"));
        testSlider.setValue(*audioProcessor.parameterTree.getRawParameterValue("BYPASS"));
    }
}