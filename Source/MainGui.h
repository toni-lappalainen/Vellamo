/*
  ==============================================================================

	MainGui.h
	Created: 6 May 2020 6:32:57pm
	Author:  tonil

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class MainGui : public juce::Component
{
public:
	MainGui(VellamoAudioProcessor&);
	~MainGui();

	void paint(juce::Graphics&) override;
	void resized() override;

private:

	Slider mMasterVolumeSlider;
	Label mMasterVolumeLabel;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mMasterVolumeAttachment;

	VellamoAudioProcessor& processor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainGui)
};
