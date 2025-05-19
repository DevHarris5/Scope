#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class ScopeAudioProcessorEditor : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    ScopeAudioProcessorEditor(ScopeAudioProcessor&);
    ~ScopeAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void timerCallback() override;

    ScopeAudioProcessor& audioProcessor;
    juce::Image scopeImage;

    juce::Slider speedSlider;
    int scrollSpeed = 50; // Default speed (samples per pixel)


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ScopeAudioProcessorEditor)
};