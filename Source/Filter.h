/*
  ==============================================================================

    Filter.h
    Created: 6 May 2020 6:33:09pm
    Author:  tonil

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Filter    : public juce::Component
{
public:
    Filter();
    ~Filter();

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Filter)
};
