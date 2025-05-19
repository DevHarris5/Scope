#include "SmoothVisualiser.h"

SmoothVisualiser::SmoothVisualiser()
    : displayMode(DisplayMode::Waveform), zoomLevel(1.0), decayFactor(0.98)
{
    currentBuffer.clear();
    setSize(600, 400); // Default size
}

SmoothVisualiser::~SmoothVisualiser() {}

void SmoothVisualiser::setDisplayMode(DisplayMode newMode)
{
    displayMode = newMode;
    repaint();
}

void SmoothVisualiser::pushBuffer(const juce::AudioBuffer<float>& buffer)
{
    currentBuffer = buffer;
    historyBuffers.add(currentBuffer);

    if (historyBuffers.size() > 100)  // Keep buffer size in check
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

        if (displayMode == DisplayMode::Waveform)
        {
            for (int j = 0; j < totalSamples - 1; ++j)
            {
                float sampleValue1 = buffer.getSample(0, j);
                float sampleValue2 = buffer.getSample(0, j + 1);
                double xPosition1 = j * pixelsPerSample;
                double xPosition2 = (j + 1) * pixelsPerSample;

                float yPosition1 = (getHeight() / 2) - (sampleValue1 * getHeight() / 2);
                float yPosition2 = (getHeight() / 2) - (sampleValue2 * getHeight() / 2);

                g.drawLine(xPosition1, yPosition1, xPosition2, yPosition2);
            }
        }
        else if (displayMode == DisplayMode::Envelope)
        {
            int samplesPerPixel = juce::jmax(1, totalSamples / getWidth());

            for (int x = 0; x < getWidth(); ++x)
            {
                int startSample = x * samplesPerPixel;
                int endSample = juce::jmin(startSample + samplesPerPixel, totalSamples);

                float minVal = 1.0f, maxVal = -1.0f;

                for (int s = startSample; s < endSample; ++s)
                {
                    float sample = buffer.getSample(0, s);
                    if (sample < minVal) minVal = sample;
                    if (sample > maxVal) maxVal = sample;
                }

                int midY = getHeight() / 2;
                int y1 = midY - (int)(maxVal * midY);
                int y2 = midY - (int)(minVal * midY);

                g.drawLine((float)x, (float)y1, (float)x, (float)y2);
            }
        }

        g.setOpacity(decayFactor);
    }
}
