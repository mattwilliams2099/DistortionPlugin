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
    driveSliderAttachment= std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameterTree, "DRIVE", driveSlider);
    driveSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 50);
    driveSlider.setRange(0.0f, 5.0f, 0.01f);
    driveSlider.setValue(1.0f);
    driveSlider.addListener(this);
    addAndMakeVisible(driveSlider);
    

    
    setSize (600, 300);
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
    driveSlider.setBounds(getLocalBounds());

}

void DistortionPluginAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) 
{
    if(slider == &driveSlider)
    audioProcessor.distortion.setFoldDrive(*audioProcessor.parameterTree.getRawParameterValue("DRIVE"));
}
