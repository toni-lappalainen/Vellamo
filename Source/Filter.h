/*
  ==============================================================================

	Filter.h
	Created: 6 May 2020 6:33:09pm
	Author:  tonil

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/*
*/
class Filter : public juce::Component
{
public:
	Filter(VellamoAudioProcessor&);
	~Filter();

	void paint(juce::Graphics&) override;
	void resized() override;

private:
	ComboBox mFilterMenu;

	Slider mCutoffSlider;
	Slider mResonanceSlider;

	Label mCutoffLabel;
	Label mResonanceLabel;

	std::unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> mFilterTypeAttachment;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mCutoffAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mResonanceAttachment;

	VellamoAudioProcessor& processor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Filter)
};
