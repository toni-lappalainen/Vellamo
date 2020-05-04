/*
  ==============================================================================

	OscillatorOne.h
	Created: 4 May 2020 10:04:29pm
	Author:  tonil

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class OscillatorOne : public juce::Component
{
public:
	OscillatorOne(VellamoAudioProcessor&);
	~OscillatorOne();

	void paint(juce::Graphics&) override;
	void resized() override;

private:
	ComboBox mOscMenu;

	ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> waveSelection;

	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> mWaveAttachment;
	VellamoAudioProcessor& processor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscillatorOne)
};
