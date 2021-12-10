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
class DistortionPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
    public juce::Slider::Listener, public juce::Button::Listener
{
public:
    DistortionPluginAudioProcessorEditor (DistortionPluginAudioProcessor&);
    ~DistortionPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider* slider) override;
    void buttonClicked(juce::Button* button) override;

private:
    void setSlider(juce::Slider& slider, float min = 0.0f, float max = 1.0f, float step = 0.01f, float default = 0.0f, juce::Colour colour = juce::Colours::silver, juce::Slider::SliderStyle style = juce::Slider::SliderStyle::LinearVertical);
    void setLabel(juce::Label& label, juce::Component& component, std::string name, bool attach = true);
    void setTitle(juce::Label& lable, std::string name);
    DistortionPluginAudioProcessor& audioProcessor;
    juce::Slider driveSlider, foldThreshSlider, offsetSlider, foldOutSlider, crushMixSlider;
    juce::Label  driveLabel,  foldThreshLabel,  offsetLabel,  foldOutLabel,  crushMixLabel,  stepsLabel;
    juce::Label folderLabel, clipperLabel, crusherLabel, utilitiesLabel;

    juce::Slider wetDrySlider;
    juce::Slider outputGainSlider;
    juce::Label wetDryLabel;
    juce::Label outputGainLabel;
    
    juce::Slider sClipInSlider, posAlphaSlider, posThreshSlider, negAlphaSlider, negThreshSlider, sClipOutSlider, clipMixSlider;
    juce::Label  sClipInLabel,  posAlphaLabel,  posThreshLabel,  negAlphaLabel,  negThreshLabel,  sClipOutLabel,  clipMixLabel;
    juce::ToggleButton symmetryToggle;
    juce::TextButton twoButton{ "2" }, fourButton{ "4" }, eightButton{ "8" }, sixteenButton{ "16" };
    juce::Label symmetryLabel;
     
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> foldThreshSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> offsetSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> foldOutSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> crushStepsSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> symmetryToggleAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> crushMixSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sClipInSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> posAlphaSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> posThreshSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> negAlphaSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> negThreshSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> sClipOutSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> clipMixSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetDrySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputGainSliderAttachment;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPluginAudioProcessorEditor)
};
