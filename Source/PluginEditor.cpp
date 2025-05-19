#include "PluginEditor.h"

ScopeAudioProcessorEditor::ScopeAudioProcessorEditor(ScopeAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    setSize(800, 400);
    speedSlider.setRange(10, 500, 1); // slower to faster
    speedSlider.setValue(scrollSpeed);
    speedSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    speedSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);
    speedSlider.onValueChange = [this]() {
        scrollSpeed = (int)speedSlider.getValue();
        };
    addAndMakeVisible(speedSlider);
    scopeImage = juce::Image(juce::Image::RGB, getWidth(), getHeight(), true);
    startTimerHz(60);
}

ScopeAudioProcessorEditor::~ScopeAudioProcessorEditor() {}

void ScopeAudioProcessorEditor::paint(juce::Graphics& g) {
    juce::Graphics imageGraphics(scopeImage);
    imageGraphics.setColour(juce::Colours::black.withAlpha(0.1f));
    imageGraphics.fillRect(scopeImage.getBounds());

    imageGraphics.setColour(juce::Colours::cyan);
    int midY = getHeight() / 2;
    int width = getWidth();
    int samplesPerPixel = scrollSpeed;
    int totalSamples = samplesPerPixel * width;
    int startIndex = (audioProcessor.writeIndex + ScopeAudioProcessor::bufferSize - totalSamples) % ScopeAudioProcessor::bufferSize;


    juce::Path waveformPath;
    waveformPath.startNewSubPath(0, midY);

    //int startIndex = (audioProcessor.writeIndex + ScopeAudioProcessor::bufferSize - width * samplesPerPixel) % ScopeAudioProcessor::bufferSize;

    for (int x = 0; x < width; ++x) {
        float sum = 0.0f;

        for (int j = 0; j < samplesPerPixel; ++j) {
            int index = (startIndex + x * samplesPerPixel + j) % ScopeAudioProcessor::bufferSize;
            sum += audioProcessor.circularBuffer[index];
        }

        float avg = sum / samplesPerPixel;
        float y = midY - avg * (midY - 10);
        waveformPath.lineTo((float)x, y);
    }

    imageGraphics.strokePath(waveformPath, juce::PathStrokeType(1.5f));
    g.drawImageAt(scopeImage, 0, 0);
}


void ScopeAudioProcessorEditor::resized() 
{
    speedSlider.setBounds(10, getHeight() - 30, getWidth() - 20, 20);
}

void ScopeAudioProcessorEditor::timerCallback() {
    repaint();
}
