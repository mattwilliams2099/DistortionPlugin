
#pragma once

#include <JuceHeader.h>
#include "DistortionClass.h"
#include "AudioUtilities.h"

//==============================================================================

class DistortionPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    DistortionPluginAudioProcessor();
    ~DistortionPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    juce::AudioProcessorValueTreeState parameterTree;
    DistortionClass distortion;
    float driveCurrent, offsetCurrent, foldThreshCurrent, fOutCurrent, crMixCurrent, 
        stepsCurrent, clipInCurrent, posAlphCurrent, posThreshCurrent, negAlphCurrent, 
        negThreshCurrent, clipOutCurrent, mixCurrent, wetDryCurrent, outputGainCurrent;
private:
    float lastVal = 0.0f;
    float drivePrev, offsetPrev = 0.0f, foldThreshPrev, fOutPrev, crMixPrev, stepsPrev, 
        clipInPrev, posAlphPrev, posThreshPrev, negAlphPrev, negThreshPrev, clipOutPrev, 
        mixPrev, wetDryPrev, outputGainPrev;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();

    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPluginAudioProcessor)
};
