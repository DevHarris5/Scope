#include "SmoothVisualiser.h"

SmoothVisualiser::SmoothVisualiser(juce::AudioProcessor& p)
    : processor(p), zoomLevel(1.0), bpm(4.0), samplesPerBeat(0.0), decayFactor(0.98)
{
    currentBuffer.clear();
    setBpm(bpm);
}

SmoothVisualiser::~SmoothVisualiser() {}

void SmoothVisualiser::setZoomLevel(double newZoomLevel)
{
    zoomLevel = newZoomLevel;
    repaint();
}

void SmoothVisualiser::setBpm(double newBpm)
{
    bpm = newBpm;
    samplesPerBeat = processor.getSampleRate() * 60.0 / bpm;  // Get sample rate from AudioProcessor
}

void SmoothVisualiser::pushBuffer(const juce::AudioBuffer<float>& buffer)
{
    currentBuffer = buffer;
    historyBuffers.add(currentBuffer);

    if (historyBuffers.size() > 100)
        historyBuffers.remove(0);

    repaint();
}

void SmoothVisualiser::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    if (historyBuffers.isEmpty())
    {
        g.setColour(juce::Colours::grey);
        g.drawText("No audio loaded", getLocalBounds(), juce::Justification::centred, true);
        return;
    }

    g.setColour(juce::Colours::white);
    for (int i = 0; i < historyBuffers.size(); ++i)
    {
        const juce::AudioBuffer<float>& buffer = historyBuffers[i];

        int totalSamples = buffer.getNumSamples();
        double pixelsPerSample = (double)getWidth() / (totalSamples * zoomLevel);

        for (int j = 0; j < totalSamples; ++j)
        {
            float sampleValue = buffer.getSample(0, j);
            double xPosition = j * pixelsPerSample;

            float yPosition = (getHeight() / 2) - (sampleValue * getHeight() / 2);
            g.drawLine(xPosition, getHeight() / 2, xPosition, yPosition);
        }

        g.setOpacity(decayFactor);
    }
}
