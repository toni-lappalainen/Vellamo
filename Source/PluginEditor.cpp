/*
  ==============================================================================

	This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VellamoAudioProcessorEditor::VellamoAudioProcessorEditor(VellamoAudioProcessor& p)
	: AudioProcessorEditor(&p), mMainGui(p), mADSR(p), mOscOneGui(p), processor(p)
{
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	addAndMakeVisible(mMainGui);
	addAndMakeVisible(mADSR);
	addAndMakeVisible(mOscOneGui);
	setSize(600, 400);
}

VellamoAudioProcessorEditor::~VellamoAudioProcessorEditor()
{
}

//==============================================================================
void VellamoAudioProcessorEditor::paint(juce::Graphics& g)
{
	g.fillAll(Colours::black);
}

void VellamoAudioProcessorEditor::resized()
{

	Rectangle<int> area = getLocalBounds();

	const int componentWidth = 200;
	const int componentHeight = 200;

	mMainGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
	mOscOneGui.setBounds(area.removeFromLeft(componentWidth).removeFromTop(componentHeight));
	mADSR.setBoundsRelative(0.0f, 0.75f, 1.0f, 0.25f);
}


