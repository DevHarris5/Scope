#pragma once

#include <JuceHeader.h>

enum class DisplayMode { Envelope, Waveform };

class SmoothVisualiser : public juce::Component
{
public:
    SmoothVisualiser();
    ~SmoothVisualiser() override;

    void setDisplayMode(DisplayMode newMode);
    DisplayMode getDisplayMode() const { return displayMode; }

    void setZoomLevel(double newZoomLevel) { zoomLevel = newZoomLevel; repaint(); }
    void setBpm(double newBpm);
    void pushBuffer(const juce::AudioBuffer<float>& buffer);

    void paint(juce::Graphics& g) override;

private:
    juce::AudioBuffer<float> currentBuffer;
    juce::Array<juce::AudioBuffer<float>> historyBuffers;

    DisplayMode displayMode = DisplayMode::Waveform;
    double zoomLevel = 1.0;
    double bpm = 120.0;
    double decayFactor = 0.98;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SmoothVisualiser)
};
