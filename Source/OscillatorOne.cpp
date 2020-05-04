/*
  ==============================================================================

	OscillatorOne.cpp
	Created: 4 May 2020 10:04:29pm
	Author:  tonil

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscillatorOne.h"

//==============================================================================
OscillatorOne::OscillatorOne(VellamoAudioProcessor& p) :
	processor(p)
{
	setSize(100, 100);

	mOscMenu.addItem("Square", 1);
	mOscMenu.addItem("Saw", 2);
	mOscMenu.addItem("Sine", 3);
	mOscMenu.setJustificationType(Justification::left);
	addAndMakeVisible(&mOscMenu);

	mWaveAttachment = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(processor.getValueTree(), "WAVETYPE", mOscMenu);
}

OscillatorOne::~OscillatorOne()
{
}

void OscillatorOne::paint(juce::Graphics& g)
{
	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	g.drawText("Oscillator One", titleArea, Justification::centredTop);


	juce::Rectangle <float> area(25, 25, 150, 150);

	g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);
}

void OscillatorOne::resized()
{
	juce::Rectangle<int> area = getLocalBounds().reduced(40);
	mOscMenu.setBounds(area.removeFromTop(30));
}
