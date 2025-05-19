#pragma once

#include <JuceHeader.h>
class SmoothVisualiser : public juce::Component
{
public:
    SmoothVisualiser(juce::AudioProcessor& processor);  // Constructor declaration
    ~SmoothVisualiser();

    void paint(juce::Graphics& g) override;
    void pushBuffer(const juce::AudioBuffer<float>& buffer);
    void setZoomLevel(double newZoomLevel);  // Set zoom level
    void setBpm(double newBpm);  // Set BPM (to sync with DAW)

private:
    juce::AudioProcessor& processor;  // Reference to the AudioProcessor to access sample rate
    juce::AudioBuffer<float> currentBuffer;
    juce::Array<juce::AudioBuffer<float>> historyBuffers;
    double zoomLevel;
    double bpm;
    double samplesPerBeat;
    double decayFactor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SmoothVisualiser)
};
