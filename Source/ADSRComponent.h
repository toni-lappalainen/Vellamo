/*
  ==============================================================================

	ADSRComponent.h
	Created: 4 May 2020 4:07:57pm
	Author:  tonil

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"


//==============================================================================
/*
*/
class ADSRComponent : public Component
{
public:
	ADSRComponent(VellamoAudioProcessor& p);
	~ADSRComponent();

	void paint(Graphics&) override;
	void resized() override;

private:
	Slider mAttackSlider, mDecaySlider, mSustainSlider, mReleaseSlider;
	Label mAttackLabel, mDecayLabel, mSustainLabel, mReleaseLabel;

	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mAttackAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mDecayAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mSustainAttachment;
	std::unique_ptr<AudioProcessorValueTreeState::SliderAttachment> mReleaseAttachment;

	VellamoAudioProcessor& processor;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ADSRComponent)
};
