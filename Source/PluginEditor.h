/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "MainGui.h"
#include "ADSRComponent.h"
#include "OscillatorOne.h"
#include "Filter.h"

//==============================================================================
/**
*/
class VellamoAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
	VellamoAudioProcessorEditor(VellamoAudioProcessor&);
	~VellamoAudioProcessorEditor();

	//==============================================================================
	void paint(juce::Graphics&) override;
	void resized() override;


private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.

	MainGui mMainGui;
	OscillatorOne mOscOneGui;
	ADSRComponent mADSR;
	Filter mFilter;

	VellamoAudioProcessor& processor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VellamoAudioProcessorEditor)
};
