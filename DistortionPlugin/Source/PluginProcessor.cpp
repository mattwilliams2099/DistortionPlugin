/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionPluginAudioProcessor::DistortionPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
    ), parameterTree(*this, nullptr, "Parameters", createParameters())
#endif
{
    parameterTree.state = juce::ValueTree("savedParams");
}

DistortionPluginAudioProcessor::~DistortionPluginAudioProcessor()
{
}

//==============================================================================
const juce::String DistortionPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DistortionPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DistortionPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DistortionPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DistortionPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DistortionPluginAudioProcessor::getNumPrograms()
{
    return 1;              
}

int DistortionPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DistortionPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DistortionPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void DistortionPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DistortionPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    /*
    drivePrev =     *parameterTree.getRawParameterValue("DRIVE");
    offsetPrev =    *parameterTree.getRawParameterValue("OFFSET");
    fOutPrev =      *parameterTree.getRawParameterValue("FOUT");
    crMixPrev =     *parameterTree.getRawParameterValue("CRMIX");
    clipInPrev =    *parameterTree.getRawParameterValue("CLIPIN");
    posAlphPrev =   *parameterTree.getRawParameterValue("PALPH");
    posThreshPrev = *parameterTree.getRawParameterValue("PTHR");
    negAlphPrev =   *parameterTree.getRawParameterValue("NALPH");
    negThreshPrev = *parameterTree.getRawParameterValue("NTHR");
    clipOutPrev =   *parameterTree.getRawParameterValue("CLIPOUT");
    mixPrev =       *parameterTree.getRawParameterValue("MIX");   */
    distortion.setSymmetryToggle(*parameterTree.getRawParameterValue("SYM"));
    distortion.setFoldOffset(*parameterTree.getRawParameterValue("OFFSET"));
    distortion.setCrushSteps(4.0f);
    foldThreshCurrent = *parameterTree.getRawParameterValue("FOLDTHR");
    foldThreshPrev = *parameterTree.getRawParameterValue("FOLDTHR");
    outputGainPrev = *parameterTree.getRawParameterValue("OUT");
}

void DistortionPluginAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DistortionPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DistortionPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    if (lastVal == 0.0f)
    {
        offsetCurrent = 0.0f;
    }
    else
    {
        offsetCurrent = *parameterTree.getRawParameterValue("OFFSET");
    }
    distortion.setFoldDrive(parameterSmooth     (driveCurrent,      drivePrev));
    distortion.setFoldOffset(parameterSmooth    (offsetCurrent,     offsetPrev));
    distortion.setFoldThresh(parameterSmooth    (foldThreshCurrent, foldThreshPrev));
    distortion.setFoldOutGain(parameterSmooth   (fOutCurrent,       fOutPrev));
    distortion.setCrushMix(parameterSmooth      (crMixCurrent,      crMixPrev));
    distortion.setSClipInGain(parameterSmooth   (clipInCurrent,     clipInPrev));
    distortion.setPosAlpha(parameterSmooth      (posAlphCurrent,    posAlphPrev));
    distortion.setSClipPosThresh(parameterSmooth(posThreshCurrent,  posThreshPrev));
    distortion.setSClipOutGain(parameterSmooth  (clipOutCurrent,    clipOutPrev));
    distortion.setMix(parameterSmooth           (mixCurrent,        mixPrev));
    distortion.setWet(parameterSmooth           (wetDryCurrent,     wetDryPrev));
    distortion.setOutputGain(parameterSmooth    (outputGainCurrent, outputGainPrev));
    distortion.setNegAlpha(parameterSmooth      (negAlphCurrent,    negAlphPrev));
    distortion.setSClipNegThresh(parameterSmooth(negThreshCurrent,  negThreshPrev));
  

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) 
        {
            lastVal = channelData[sample];
            channelData[sample] = distortion.distortionProcess(channelData[sample]);   
        }
    }    
    drivePrev = distortion.getFoldDrive();
    offsetPrev = distortion.getFoldOffset();
    fOutPrev = distortion.getFoldOutGain();
    foldThreshPrev = distortion.getFoldThresh();
    crMixPrev = distortion.getCrushMix();
    clipInPrev = distortion.getSClipInGain();
    posAlphPrev = distortion.getPosAlpha();
    posThreshPrev = distortion.getSClipPosThresh();
    negAlphPrev = distortion.getNegAlpha();
    negThreshPrev = distortion.getSClipNegThresh();
    clipOutPrev = distortion.getSClipOutGain();
    mixPrev = distortion.getMix();
    wetDryPrev = distortion.getWet();
    outputGainPrev = distortion.getOutputGain();
}

//==============================================================================
bool DistortionPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DistortionPluginAudioProcessor::createEditor()
{
    return new DistortionPluginAudioProcessorEditor (*this);
}

//==============================================================================
void DistortionPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DistortionPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DistortionPluginAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout DistortionPluginAudioProcessor::createParameters() 
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters;
    parameters.push_back(std::make_unique <juce::AudioParameterFloat> ("DRIVE", "Drive",            0.0f,   5.0f,   1.0f));
    parameters.push_back(std::make_unique <juce::AudioParameterFloat> ("FOLDTHR", "Fold Thresh",    0.0f,   1.0f,   1.0f));
    parameters.push_back(std::make_unique <juce::AudioParameterFloat> ("OFFSET","Offset",           -0.5f, 0.5f,  0.0f));
    parameters.push_back(std::make_unique <juce::AudioParameterFloat> ("FOUT",  "Output",           0.0f,   3.0f,   1.0f));
    parameters.push_back(std::make_unique <juce::AudioParameterFloat>("CRMIX",  "Crush Mix",        0.0f,   1.0f,   1.0f));
    parameters.push_back(std::make_unique <juce::AudioParameterFloat>("CLIPIN", "Pre Clip Gain",    0.0f,   2.5f,   1.0f));
    parameters.push_back(std::make_unique <juce::AudioParameterFloat>("PALPH",  "Pos Alpha",        0.1f,   20.0f,  1.0f));
    parameters.push_back(std::make_unique <juce::AudioParameterFloat>("PTHR",   "Pos Threshold",    0.0f,   1.0f,   1.0f));
    parameters.push_back(std::make_unique <juce::AudioParameterFloat>("NALPH",  "Neg Alpha",        0.1f,   20.0f,  1.0f));
    parameters.push_back(std::make_unique <juce::AudioParameterFloat>("NTHR",   "Neg Threshold",    -1.0f,  1.0f,   1.0f));
    parameters.push_back(std::make_unique <juce::AudioParameterFloat>("CLIPOUT","Post Clip Gain",   0.0f,   1.5f,   1.0f));
    parameters.push_back(std::make_unique <juce::AudioParameterFloat>("MIX",    "Mix",              0.0f,   1.0f,   0.5f));
    parameters.push_back(std::make_unique <juce::AudioParameterBool>  ("SYM",   "SYMMETRY",         false));
    parameters.push_back(std::make_unique <juce::AudioParameterFloat>("WDMIX", "WetDryMix", 0.0f, 1.0f, 1.0f));
    parameters.push_back(std::make_unique <juce::AudioParameterFloat>("OUT", "Output", 0.0f, 1.3f, 1.0f));
    return { parameters.begin(), parameters.end() };
}

