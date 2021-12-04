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
    DistortionPluginAudioProcessor& audioProcessor;
    
    juce::Slider foldInGainSlider, foldsSlider, foldOffsetSlider, foldOutGainSlider;
    juce::Label foldInGainLabel, foldsLabel, foldOffsetLabel, foldOutGainLabel;

    juce::Slider rectInGainSlider, rectThreshSlider, rectOutGainSlider;
    juce::Label rectInGainLabel, rectThreshLabel, rectOutGainLabel;

    juce::Slider sClipInGainSlider, posAlphaSlider, sClipPosThreshSlider, negAlphaSlider, sClipNegThreshSlider, sClipOutGainSlider;
    juce::Label sClipInGainLabel, posAlphaLabel, sClipPosThreshLabel, negAlphaLabel, sClipNegThreshLabel, sClipOutGainLabel;

    juce::Slider crushStepsSlider;
    juce::ToggleButton crushBypassButton;
    juce::Label crushStepsLabel, crushBypassLabel;
   



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPluginAudioProcessorEditor)
};
