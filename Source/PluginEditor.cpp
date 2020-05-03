/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VellamoAudioProcessorEditor::VellamoAudioProcessorEditor(VellamoAudioProcessor& p)
	: AudioProcessorEditor(&p), processor(p)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.

	//Attack Slider
	mAttackSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	mAttackSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	mAttackSlider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
	addAndMakeVisible(mAttackSlider);

	mAttackLabel.setFont(10.0f);
	mAttackLabel.setText("Attack", NotificationType::dontSendNotification);
	mAttackLabel.setJustificationType(Justification::centredTop);
	mAttackLabel.attachToComponent(&mAttackSlider, false);

	mAttackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTree(), "ATTACK", mAttackSlider);

	//Decay Slider
	mDecaySlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	mDecaySlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	mDecaySlider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
	addAndMakeVisible(mDecaySlider);

	mDecayLabel.setFont(10.0f);
	mDecayLabel.setText("Decay", NotificationType::dontSendNotification);
	mDecayLabel.setJustificationType(Justification::centredTop);
	mDecayLabel.attachToComponent(&mDecaySlider, false);

	mDecayAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTree(), "DECAY", mDecaySlider);

	//Sustain Slider
	mSustainSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	mSustainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	mSustainSlider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
	addAndMakeVisible(mSustainSlider);

	mSustainLabel.setFont(10.0f);
	mSustainLabel.setText("Sustain", NotificationType::dontSendNotification);
	mSustainLabel.setJustificationType(Justification::centredTop);
	mSustainLabel.attachToComponent(&mSustainSlider, false);

	mSustainAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTree(), "SUSTAIN", mSustainSlider);

	//Release Slider
	mReleaseSlider.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
	mReleaseSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 40, 20);
	mReleaseSlider.setColour(Slider::ColourIds::thumbColourId, Colours::red);
	addAndMakeVisible(mReleaseSlider);

	mReleaseLabel.setFont(10.0f);
	mReleaseLabel.setText("Release", NotificationType::dontSendNotification);
	mReleaseLabel.setJustificationType(Justification::centredTop);
	mReleaseLabel.attachToComponent(&mReleaseSlider, false);

	mReleaseAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.getValueTree(), "RELEASE", mReleaseSlider);

	/*
	attackVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "attack", mAttackSlider);
	decayVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "decay", mDecaySlider);
	sustainVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "sustain", mSustainSlider);
	releaseVal = new AudioProcessorValueTreeState::SliderAttachment(processor.tree, "release", mReleaseSlider);
	*/
	setSize(600, 200);
}

VellamoAudioProcessorEditor::~VellamoAudioProcessorEditor()
{
}

//==============================================================================
void VellamoAudioProcessorEditor::paint(juce::Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

	g.setColour(juce::Colours::white);
	g.setFont(15.0f);
	g.drawFittedText("Vellamo", getLocalBounds(), juce::Justification::centred, 1);
}

void VellamoAudioProcessorEditor::resized()
{
	const auto startX = 0.6f;
	const auto startY = 0.6f;
	const auto dialWidth = 0.1f;
	const auto dialHeight = 0.4f;

	mAttackSlider.setBoundsRelative(startX, startY, dialWidth, dialHeight);
	mDecaySlider.setBoundsRelative(startX + dialWidth, startY, dialWidth, dialHeight);
	mSustainSlider.setBoundsRelative(startX + (dialWidth * 2), startY, dialWidth, dialHeight);
	mReleaseSlider.setBoundsRelative(startX + (dialWidth * 3), startY, dialWidth, dialHeight);
}


