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
    
    //driveSlider.setValue(1.0f);
    driveSlider.addListener(this);
    driveSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "DRIVE", driveSlider);
    driveSlider.setRange(0.0f, 5.0f, 0.01f);
    addAndMakeVisible(driveSlider);

    
    foldsSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    foldsSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    
    //foldsSlider.setValue(1.0f);
    foldsSlider.addListener(this);
    foldsSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "FOLDS", foldsSlider);
    foldsSlider.setRange(1.0f, 8.0f, 1.0f);
    addAndMakeVisible(foldsSlider);

    
    offsetSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    offsetSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    ;
    //offsetSlider.setValue(0.0f);
    offsetSlider.addListener(this);
    offsetSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "OFFSET", offsetSlider);
    offsetSlider.setRange(-0.75f, 0.75f, 0.01f);
    addAndMakeVisible(offsetSlider);

    
    foldOutSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    foldOutSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    
    //foldOutSlider.setValue(1.0f);
    foldOutSlider.addListener(this);
    foldOutSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "FOUT", foldOutSlider);
    foldOutSlider.setRange(0.0f, 5.0f, 0.01f);
    addAndMakeVisible(foldOutSlider);
    
    
    crushStepsSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    crushStepsSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
   
    //crushStepsSlider.setValue(4.0f);
    crushStepsSlider.addListener(this);
    crushStepsSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "STEPS", crushStepsSlider);
    crushStepsSlider.setRange(4.0f, 16.0f, 4.0f);
    
    addAndMakeVisible(crushStepsSlider);

    
    testSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    testSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    testSlider.setRange(-1.0f, 16.0f, 0.01f);
    testSlider.setValue(0.0f);
    addAndMakeVisible(testSlider);
    setSize (700, 300);
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
    driveSlider.setBounds(20, 10, 150, 150);
    foldsSlider.setBounds(120, 10, 150, 150);
    offsetSlider.setBounds(220, 10, 150, 150);
    foldOutSlider.setBounds(320, 10, 150, 150);
    crushStepsSlider.setBounds(440, 10, 150, 150);
    testSlider.setBounds(100, 200, 300, 50);
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

}
