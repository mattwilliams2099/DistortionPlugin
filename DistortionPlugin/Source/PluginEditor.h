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
    void setSlider(juce::Slider& slider, float min = 0.0f, float max = 1.0f, float step = 0.01f, float start = 1.0f, juce::Colour colour = juce::Colours::black);
    void setLabel(juce::Label& label, juce::Slider& slider, std::string name);
    //void setButton(juce::ToggleButton& button);
    DistortionPluginAudioProcessor& audioProcessor;
    juce::Slider driveSlider, foldsSlider, offsetSlider, foldOutSlider, crushStepsSlider, crushMixSlider;
    juce::Slider sClipInSlider, posAlphaSlider, posThreshSlider, negAlphaSlider, negThreshSlider, sClipOutSlider, clipMixSlider;
    juce::ToggleButton symmetryToggle;
    juce::TextButton twoButton{ "2" }, fourButton{ "4" }, eightButton{ "8" }, sixteenButton{ "16" };
    juce::Label driveLabel, foldsLabel, offsetLabel, foldOutLabel, stepsLabel, crushMixLabel;
    juce::Label symmetryLabel;
    juce::Label sClipInLabel, 
                posAlphaLabel, 
                posThreshLabel, 
                negAlphaLabel, 
                negThreshLabel,     
                sClipOutLabel, 
                clipMixLabel;

    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> foldsSliderAttachment;
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


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPluginAudioProcessorEditor)
};
