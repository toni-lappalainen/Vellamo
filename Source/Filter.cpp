/*
  ==============================================================================

	Filter.cpp
	Created: 6 May 2020 6:33:09pm
	Author:  tonil

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Filter.h"

//==============================================================================
Filter::Filter(VellamoAudioProcessor& p) : processor(p)
{

	setSize(100, 100);

	mFilterMenu.addItem("LP", 1);
	mFilterMenu.addItem("BP", 2);
	mFilterMenu.addItem("HP", 3);
	mFilterMenu.setJustificationType(Justification::left);
	addAndMakeVisible(&mFilterMenu);

	mFilterTypeAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.getValueTree(), "FILTERTYPE", mFilterMenu);

	mCutoffSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	mCutoffSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	mCutoffSlider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
	addAndMakeVisible(mCutoffSlider);

	mCutoffLabel.setFont(12.0f);
	mCutoffLabel.setText("Cutoff", NotificationType::dontSendNotification);
	mCutoffLabel.setJustificationType(Justification::centredTop);
	mCutoffLabel.attachToComponent(&mCutoffSlider, false);

	mCutoffAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTree(), "CUTOFF", mCutoffSlider);


	mResonanceSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	mResonanceSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	mResonanceSlider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
	addAndMakeVisible(mResonanceSlider);

	mResonanceLabel.setFont(12.0f);
	mResonanceLabel.setText("Resonance", NotificationType::dontSendNotification);
	mResonanceLabel.setJustificationType(Justification::centredTop);
	mResonanceLabel.attachToComponent(&mResonanceSlider, false);

	mResonanceAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTree(), "RESONANCE", mResonanceSlider);
}

Filter::~Filter()
{
}

void Filter::paint(juce::Graphics& g)
{

	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Filter", titleArea, Justification::centredTop);


	juce::Rectangle <float> area(25, 25, 150, 150);

	g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void Filter::resized()
{
	juce::Rectangle<int> area = getLocalBounds().reduced(40);
	mFilterMenu.setBounds(area.removeFromTop(30));
	mCutoffSlider.setBounds(30, 100, 70, 70);
	mResonanceSlider.setBounds(100, 100, 70, 70);
}
