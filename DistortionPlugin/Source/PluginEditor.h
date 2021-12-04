/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DistortionPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DistortionPluginAudioProcessorEditor (DistortionPluginAudioProcessor&);
    ~DistortionPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    
    juce::Slider driveSlider, foldsSlider, offsetSlider, fOutputSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> foldsSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> offsetSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fOutputSliderAttachment;
    
    
    DistortionPluginAudioProcessor& audioProcessor;
    /*
    juce::Slider foldsSlider, foldOffsetSlider, foldOutGainSlider;
    juce::Label foldInGainLabel, foldsLabel, foldOffsetLabel, foldOutGainLabel;

    juce::Slider rectInGainSlider, rectThreshSlider, rectOutGainSlider;
    juce::Label rectInGainLabel, rectThreshLabel, rectOutGainLabel;

    juce::Slider sClipInGainSlider, posAlphaSlider, sClipPosThreshSlider, negAlphaSlider, sClipNegThreshSlider, sClipOutGainSlider;
    juce::Label sClipInGainLabel, posAlphaLabel, sClipPosThreshLabel, negAlphaLabel, sClipNegThreshLabel, sClipOutGainLabel;

    juce::Slider crushStepsSlider;
    juce::ToggleButton crushBypassButton;
    juce::Label crushStepsLabel, crushBypassLabel;
   */



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPluginAudioProcessorEditor)
};
