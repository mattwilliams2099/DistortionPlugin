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
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 30);
    driveSlider.addListener(this);
    driveSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "DRIVE", driveSlider);
    driveSlider.setRange(0.0f, 5.0f, 0.01f);
    driveSlider.setValue(1.0f);
    addAndMakeVisible(driveSlider);
    driveLabel.setText("DRIVE", juce::dontSendNotification);
    driveLabel.attachToComponent(&driveSlider, false);
    addAndMakeVisible(driveLabel);
    
    foldsSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    foldsSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 30);
    foldsSlider.addListener(this);
    foldsSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "FOLDS", foldsSlider);
    foldsSlider.setRange(1.0f, 8.0f, 1.0f);
    foldsSlider.setValue(1.0f);
    addAndMakeVisible(foldsSlider);
    foldsLabel.setText("FOLDS", juce::dontSendNotification);
    foldsLabel.attachToComponent(&foldsSlider, false);
    addAndMakeVisible(foldsLabel);
    
    offsetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    offsetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 30);
    offsetSlider.addListener(this);
    offsetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "OFFSET", offsetSlider);
    offsetSlider.setRange(-0.75f, 0.75f, 0.01f);
    offsetSlider.setValue(0.0f);
    addAndMakeVisible(offsetSlider);
    offsetLabel.setText("BIAS", juce::dontSendNotification);
    offsetLabel.attachToComponent(&offsetSlider, false);
    addAndMakeVisible(offsetLabel);

    
    foldOutSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    foldOutSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 30);
    foldOutSlider.addListener(this);
    foldOutSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "FOUT", foldOutSlider);
    foldOutSlider.setRange(0.0f, 5.0f, 0.01f);
    foldOutSlider.setValue(1.0f);
    addAndMakeVisible(foldOutSlider);
    foldOutLabel.setText("OUTPUT GAIN", juce::dontSendNotification);
    foldOutLabel.attachToComponent(&foldOutSlider, false);
    addAndMakeVisible(foldOutLabel);
    
    crushStepsSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    crushStepsSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 30);
    crushStepsSlider.addListener(this);
    crushStepsSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "STEPS", crushStepsSlider);
    crushStepsSlider.setRange(4.0f, 16.0f, 4.0f);
    crushStepsSlider.setValue(4.0f);
    addAndMakeVisible(crushStepsSlider);
    stepsLabel.setText("STEPS", juce::dontSendNotification);
    stepsLabel.attachToComponent(&crushStepsSlider, false);
    addAndMakeVisible(stepsLabel);

    symmetryToggle.addListener(this);
    symmetryToggleAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.parameterTree, "SYM", symmetryToggle);
    symmetryToggle.setToggleState(false, juce::dontSendNotification);
    addAndMakeVisible(symmetryToggle);
    symmetryLabel.setText("SYMMETRY", juce::dontSendNotification);
    symmetryLabel.attachToComponent(&symmetryToggle, false);
    addAndMakeVisible(symmetryLabel);
   
    crushMixSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    crushMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 30);
    crushMixSlider.addListener(this);
    crushMixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "CRMIX", crushMixSlider);
    crushMixSlider.setRange(0.0f, 1.0f, 0.01f);
    crushMixSlider.setValue(0.5f);
    addAndMakeVisible(crushMixSlider);
    crushMixLabel.setText("MIX", juce::dontSendNotification);
    crushMixLabel.attachToComponent(&crushMixSlider, false);
    addAndMakeVisible(crushMixLabel);
    
    sClipInSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sClipInSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 30);
    sClipInSlider.addListener(this);
    sClipInSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "CLIPIN", sClipInSlider);
    sClipInSlider.setRange(0.0f, 1.5f, 0.01f);
    sClipInSlider.setValue(1.0f);
    addAndMakeVisible(sClipInSlider);
    sClipInLabel.setText("DRIVE", juce::dontSendNotification);
    sClipInLabel.attachToComponent(&sClipInSlider, false);
    addAndMakeVisible(sClipInLabel);

    posAlphaSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    posAlphaSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 30);
    posAlphaSlider.addListener(this);
    posAlphaSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "PALPH", posAlphaSlider);
    posAlphaSlider.setRange(0.1f, 20.0f, 0.01f);
    posAlphaSlider.setValue(1.0f);
    addAndMakeVisible(posAlphaSlider);
    posAlphaLabel.setText("POS ALPHA", juce::dontSendNotification);
    posAlphaLabel.attachToComponent(&posAlphaSlider, false);
    addAndMakeVisible(posAlphaLabel);

    posThreshSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    posThreshSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 30);
    posThreshSlider.addListener(this);
    posThreshSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "PTHR", posThreshSlider);
    posThreshSlider.setRange(0.0f, 1.0f, 0.01f);
    posThreshSlider.setValue(1.0f);
    addAndMakeVisible(posThreshSlider);
    posThreshLabel.setText("POS THRESHOLD", juce::dontSendNotification);
    posThreshLabel.attachToComponent(&posThreshSlider, false);
    addAndMakeVisible(posThreshLabel);

    negAlphaSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    negAlphaSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 30);
    negAlphaSlider.addListener(this);
    negAlphaSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "NALPH", negAlphaSlider);
    negAlphaSlider.setRange(0.1f, 20.0f, 0.01f);
    negAlphaSlider.setValue(1.0f);
    addAndMakeVisible(negAlphaSlider);
    negAlphaLabel.setText("NEG ALPHA", juce::dontSendNotification);
    negAlphaLabel.attachToComponent(&negAlphaSlider, false);
    addAndMakeVisible(negAlphaLabel);

    negThreshSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    negThreshSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 30);
    negThreshSlider.addListener(this);
    negThreshSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "NTHR", negThreshSlider);
    negThreshSlider.setRange(0.0f, 1.0f, 0.01f);
    negThreshSlider.setValue(1.0f);
    addAndMakeVisible(negThreshSlider);
    negThreshLabel.setText("NEG THRESHOLD", juce::dontSendNotification);
    negThreshLabel.attachToComponent(&negThreshSlider, false);
    addAndMakeVisible(negThreshLabel);

    sClipOutSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sClipOutSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 30);
    sClipOutSlider.addListener(this);
    sClipOutSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "CLIPOUT", sClipOutSlider);
    sClipOutSlider.setRange(0.0f, 1.5f, 0.01f);
    sClipOutSlider.setValue(1.0f);
    addAndMakeVisible(sClipOutSlider);
    sClipOutLabel.setText("OUTPUT GAIN", juce::dontSendNotification);
    sClipOutLabel.attachToComponent(&sClipOutSlider, false);
    addAndMakeVisible(sClipOutLabel);
    
    clipMixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    clipMixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 40, 30);
    clipMixSlider.addListener(this);
    clipMixSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "MIX", clipMixSlider);
    clipMixSlider.setRange(0.0f, 1.0f, 0.01f);
    clipMixSlider.setValue(0.5f);
    addAndMakeVisible(clipMixSlider);
    clipMixLabel.setText("MIX", juce::dontSendNotification);
    clipMixLabel.attachToComponent(&clipMixSlider, false);
    addAndMakeVisible(clipMixLabel);

   
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
    driveSlider.setBounds       (20,  40, 100, 100);
    foldsSlider.setBounds       (120, 40, 100, 100);
    offsetSlider.setBounds      (220, 40, 100, 100);
    foldOutSlider.setBounds     (320, 40, 100, 100);
    crushStepsSlider.setBounds  (520, 40, 100, 100);
    
    crushMixSlider.setBounds    (620, 40, 100, 100);

    sClipInSlider.setBounds     (20,  200, 100, 100);
    posAlphaSlider.setBounds    (120, 200, 100, 100);
    posThreshSlider.setBounds   (220, 200, 100, 100);
    symmetryToggle.setBounds    (350, 200, 50, 50);
    negAlphaSlider.setBounds    (420, 200, 100, 100);
    negThreshSlider.setBounds   (520, 200, 100, 100);
    sClipOutSlider.setBounds    (620, 200, 100, 100);
    clipMixSlider.setBounds     (750, 40, 40, 260);

}

void DistortionPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) 
{
    /*if (slider == &driveSlider) {
        audioProcessor.distortion.setFoldDrive(*audioProcessor.parameterTree.getRawParameterValue("DRIVE"));
        
    }
    */if (slider == &foldsSlider) {
        audioProcessor.distortion.setFolds(*audioProcessor.parameterTree.getRawParameterValue("FOLDS"));
        
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
}