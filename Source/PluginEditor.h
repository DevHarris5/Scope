#pragma once

#include <JuceHeader.h>
#include "SmoothVisualiser.h"

class ScopeAudioProcessorEditor : public juce::AudioProcessorEditor
{
public:
    ScopeAudioProcessorEditor(juce::AudioProcessor&);
    ~ScopeAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void pushBuffer(const juce::AudioBuffer<float>& buffer);

private:
    //juce::AudioVisualiserComponent visualiser;
    SmoothVisualiser visualiser;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScopeAudioProcessorEditor)
};
