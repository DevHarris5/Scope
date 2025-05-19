#pragma once

#include <JuceHeader.h>

class SmoothVisualiser : public juce::Component,
    private juce::Timer
{
public:
    SmoothVisualiser()
    {
        setOpaque(true);
        startTimerHz(30); // refresh rate
    }

    void pushBuffer(const juce::AudioBuffer<float>& buffer)
    {
        const int numSamples = buffer.getNumSamples();
        const float* readDataL = buffer.getReadPointer(0);
        const float* readDataR = buffer.getNumChannels() > 1 ? buffer.getReadPointer(1) : nullptr;

        for (int i = 0; i < numSamples; ++i)
        {
            float sample = readDataL[i];
            if (readDataR != nullptr)
                sample = 0.5f * (sample + readDataR[i]); // average stereo

            waveform.add(sample);

            // Limit size of waveform buffer
            if (waveform.size() > 1024)
                waveform.remove(0);
        }
    }

    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::black);

        juce::Path path;
        auto w = getWidth();
        auto h = getHeight();

        if (waveform.isEmpty()) return;

        const int size = waveform.size();
        const float xStep = (float)w / (float)size;
        float midY = h * 0.5f;

        path.startNewSubPath(0, midY - waveform.getUnchecked(0) * midY);

        for (int i = 1; i < size; ++i)
        {
            float x = i * xStep;
            float y = midY - waveform.getUnchecked(i) * midY;
            path.lineTo(x, y);
        }

        g.setColour(juce::Colours::lime);
        g.strokePath(path, juce::PathStrokeType(2.0f));
    }

private:
    void timerCallback() override
    {
        repaint();
    }

    juce::Array<float> waveform;
};
