/*
  ==============================================================================

	SynthVoice.h
	Created: 3 May 2020 9:09:00am
	Author:  tonil

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthSound.h"
#include "maximilian.h"

using namespace juce;

class SynthVoice : public SynthesiserVoice
{
public:
	bool canPlaySound(SynthesiserSound* sound) override
	{
		return dynamic_cast <SynthSound*>(sound) != nullptr;
	}

	void getParam(AudioParameterFloat* attack)
	{
		env1.setAttack(double(*attack));
	}

	void setPitchBend(int pitchWheelPos)
	{
		if (pitchWheelPos > 8192)
		{
			// shifting up
			pitchBend = float(pitchWheelPos - 8192) / (16383 - 8192);
		}
		else
		{
			// shifting down
			pitchBend = float(8192 - pitchWheelPos) / -8192;    // negative number
		}
	}

	float pitchBendCents()
	{
		if (pitchBend >= 0.0f)
		{
			// shifting up
			return pitchBend * pitchBendUpSemitones * 100;
		}
		else
		{
			// shifting down
			return pitchBend * pitchBendDownSemitones * 100;
		}
	}

	static double noteHz(int midiNoteNumber, double centsOffset)
	{
		double hertz = MidiMessage::getMidiNoteInHertz(midiNoteNumber);
		hertz *= std::pow(2.0, centsOffset / 1200);
		return hertz;
	}

	//=======================================================

	void setADSRSampleRate(double sampleRate)
	{
		mADSR.setSampleRate(sampleRate);
	}

	//=======================================================

	void getOscOneType(String selection)
	{
		String square = "Square";
		String saw = "Saw";

		if (square == selection)
		{
			waveOne = 0;
		}
		if (saw == selection)
			waveOne = 1;
		else
			waveOne = 2;

	}

	//=======================================================

	double setOscType()
	{
		double sample1;

		switch (waveOne)
		{
		case 0:
			sample1 = osc1.square(frequency);
			break;
		case 1:
			sample1 = osc1.saw(frequency);
			break;
		default:
			sample1 = osc1.sinewave(frequency);
			break;
		}

		return sample1;
	}

	//=======================================================

	void getEnvelopeParams(float* attack, float* decay, float* sustain, float* release)
	{
		adsrParams.attack = *attack;
		adsrParams.decay = *decay;
		adsrParams.sustain = *sustain;
		adsrParams.release = *release;
	}

	ADSR::Parameters getParams()
	{
		return adsrParams;
	}

	//=======================================================

	void startNote(int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override
	{
		mADSR.noteOn();
		noteNumber = midiNoteNumber;
		setPitchBend(currentPitchWheelPosition);
		frequency = noteHz(noteNumber, pitchBendCents());
		level = velocity;
	}

	//=======================================================

	void stopNote(float velocity, bool allowTailOff) override
	{
		mADSR.noteOff();
		allowTailOff = true;

		if (velocity == 0)
			clearCurrentNote();
	}

	//=======================================================

	void pitchWheelMoved(int newPitchWheelValue) override
	{
		setPitchBend(newPitchWheelValue);
		frequency = noteHz(noteNumber, pitchBendCents());
	}

	//=======================================================

	void controllerMoved(int controllerNumber, int newControllerValue) override
	{

	}

	//=======================================================

	double setEnvelope()
	{
		//	double test = setOscType();
		return mADSR.getNextSample() * setOscType();
	}

	//=======================================================

	void renderNextBlock(AudioBuffer <float>& outputBuffer, int startSample, int numSamples) override
	{
		mADSR.setParameters(adsrParams);

		for (int sample = 0; sample < numSamples; ++sample)
		{

			for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
			{
				outputBuffer.addSample(channel, startSample, setEnvelope() * 0.3f);
			}
			++startSample;
		}
	}

	//=======================================================
private:
	double level;
	double frequency;

	int waveOne;

	String test;

	maxiOsc osc1;
	maxiEnv env1;
	maxiFilter filter1;

	float masterGain;

	int noteNumber;
	float pitchBend = 0.0f;
	float pitchBendUpSemitones = 2.0f;
	float pitchBendDownSemitones = 2.0f;

	float cutoff;
	float resonance;

	ADSR mADSR;
	ADSR::Parameters adsrParams;

};
