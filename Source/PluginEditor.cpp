#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SmoothVisualiser.h"



ScopeAudioProcessorEditor::ScopeAudioProcessorEditor(juce::AudioProcessor& p)
    : AudioProcessorEditor(&p), visualiser()  // Pass processor to visualiser
{
    setSize(600, 400);
    addAndMakeVisible(visualiser);

    // Set up zoom slider
    zoomSlider.setRange(0.1, 5.0, 0.1);  // Zoom level between 0.1x and 5x
    zoomSlider.setValue(1.0);  // Start at normal zoom
    zoomSlider.onValueChange = [this] {
        // Update zoom level in the visualiser when the slider value changes
        visualiser.setZoomLevel(zoomSlider.getValue());
        };
    zoomSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    zoomSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 50, 20); // Value below slider
    zoomSlider.setColour(juce::Slider::thumbColourId, juce::Colours::orange);  // Thumb color
    zoomSlider.setColour(juce::Slider::trackColourId, juce::Colours::darkgrey);  // Track color
    zoomSlider.setColour(juce::Slider::backgroundColourId, juce::Colours::lightgrey);  // Background color
    addAndMakeVisible(zoomSlider);  // Make the slider visible
}

ScopeAudioProcessorEditor::~ScopeAudioProcessorEditor() {}

void ScopeAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void ScopeAudioProcessorEditor::resized()
{
    visualiser.setBounds(getLocalBounds().removeFromTop(getHeight() - 50));  // Resize visualizer
    zoomSlider.setBounds(10, getHeight() - 40, getWidth() - 20, 30);  // Position zoom slider
    DBG("Slider bounds: " << zoomSlider.getBounds().toString()); // Debugging slider position
}

void ScopeAudioProcessorEditor::pushBuffer(const juce::AudioBuffer<float>& buffer)
{
    // Combine left and right channels into mono
    juce::AudioBuffer<float> monoBuffer(1, buffer.getNumSamples());
    monoBuffer.clear();

    auto* monoData = monoBuffer.getWritePointer(0);

    // Combine left and right channels into mono by averaging them
    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
    {
        monoBuffer.addFrom(0, 0, buffer, ch, 0, buffer.getNumSamples(), 0.5f);  // Average L+R channels
    }

    // Push the mono buffer to the visualiser
    visualiser.pushBuffer(monoBuffer);
}


