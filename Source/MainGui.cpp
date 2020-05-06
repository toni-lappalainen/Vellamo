/*
  ==============================================================================

	MasterGui.cpp
	Created: 6 May 2020 6:32:57pm
	Author:  tonil

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MainGui.h"

//==============================================================================
MainGui::MainGui(VellamoAudioProcessor& p) :
	processor(p)
{
	setSize(100, 100);

	mMasterVolumeSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	mMasterVolumeSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 30);
	mMasterVolumeSlider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
	addAndMakeVisible(&mMasterVolumeSlider);
	mMasterVolumeSlider.textFromValueFunction = [](float value)
	{
		int feedback = (value * (100.0f));
		return juce::String(feedback);
	};

	mMasterVolumeLabel.setFont(12.0f);
	mMasterVolumeLabel.setText("Master Volume", NotificationType::dontSendNotification);
	mMasterVolumeLabel.setJustificationType(Justification::centredTop);
	mMasterVolumeLabel.attachToComponent(&mMasterVolumeSlider, false);

	mMasterVolumeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTree(), "MASTER", mMasterVolumeSlider);

}

MainGui::~MainGui()
{
}

void MainGui::paint(juce::Graphics& g)
{
	juce::Rectangle<int> titleArea(0, 10, getWidth(), 20);

	g.fillAll(Colours::black);
	g.setColour(Colours::white);
	//	g.drawText("Main", titleArea, Justification::centredTop);

		//static positioning for now due to time, make dynamic later
	//	g.drawText("Master", 53, 40, 40, 20, Justification::centredLeft);

	juce::Rectangle<float> area(25, 25, 150, 150);

	g.setColour(Colours::yellow);
	g.drawRoundedRectangle(area, 20.0f, 2.0f);

}

void MainGui::resized()
{
	//draws the sliders...we use a rectangle object to dynamically size the UI (if we want to resize for IPad etc without needing to change ALL settings
	juce::Rectangle<int> area = getLocalBounds().reduced(50);

	int sliderWidth = 25;
	int sliderHeight = 25;

	//draw sliders by reducing area from rectangle above

	mMasterVolumeSlider.setBounds(45, 20, 120, 100);

}
