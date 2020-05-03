/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VellamoAudioProcessor::VellamoAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
		),
	tree(*this, nullptr, "PARAMETERS",
		{ std::make_unique<AudioParameterFloat>("attack", "Attack", NormalisableRange<float>(0.1f, 5.0f), 0.1f),
			std::make_unique<AudioParameterFloat>("decay", "Decay", NormalisableRange<float>(0.1f, 2.0f), 0.8f),
			std::make_unique<AudioParameterFloat>("sustain", "Sustain", NormalisableRange<float>(0.1f, 1.0f), 0.8f),
			std::make_unique<AudioParameterFloat>("release", "Release", NormalisableRange<float>(0.1f, 5.0f), 0.1f),
		})
#endif
{

	mSynth.clearVoices();

	for (int i = 0; i < mNumVoices; i++)
	{
		mSynth.addVoice(new SynthVoice());
	}

	mSynth.clearSounds();
	mSynth.addSound(new SynthSound());
}

VellamoAudioProcessor::~VellamoAudioProcessor()
{
}

//==============================================================================
const juce::String VellamoAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool VellamoAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool VellamoAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool VellamoAudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double VellamoAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int VellamoAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int VellamoAudioProcessor::getCurrentProgram()
{
	return 0;
}

void VellamoAudioProcessor::setCurrentProgram(int index)
{
}

const juce::String VellamoAudioProcessor::getProgramName(int index)
{
	return {};
}

void VellamoAudioProcessor::changeProgramName(int index, const juce::String& newName)
{
}

//==============================================================================
void VellamoAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	ignoreUnused(samplesPerBlock);
	lastSampleRate = sampleRate;
	mSynth.setCurrentPlaybackSampleRate(lastSampleRate);
}

void VellamoAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool VellamoAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	juce::ignoreUnused(layouts);
	return true;
#else
	// This is the place where you check if the layout is supported.
	// In this template code we only support mono or stereo.
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

void VellamoAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();


	for (int i = 0; i < mSynth.getNumVoices(); i++)
	{
		if ((mVoice = dynamic_cast<SynthVoice*>(mSynth.getVoice(i))))
		{
			mVoice->setADSRSampleRate(lastSampleRate);
			mVoice->getEnvelopeParams((float*)tree.getRawParameterValue("attack"),
				(float*)tree.getRawParameterValue("decay"),
				(float*)tree.getRawParameterValue("sustain"),
				(float*)tree.getRawParameterValue("release"));
		}
	}

	buffer.clear();

	mSynth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool VellamoAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* VellamoAudioProcessor::createEditor()
{
	return new VellamoAudioProcessorEditor(*this);
}

//==============================================================================
void VellamoAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void VellamoAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new VellamoAudioProcessor();
}

