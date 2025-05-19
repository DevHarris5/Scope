#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "SmoothVisualiser.h"



ScopeAudioProcessorEditor::ScopeAudioProcessorEditor(juce::AudioProcessor& p)
    : AudioProcessorEditor(&p) // stereo
{
    setSize(600, 400);
    addAndMakeVisible(visualiser);
}

ScopeAudioProcessorEditor::~ScopeAudioProcessorEditor() {}

void ScopeAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void ScopeAudioProcessorEditor::resized()
{
    visualiser.setBounds(getLocalBounds());
}

void ScopeAudioProcessorEditor::pushBuffer(const juce::AudioBuffer<float>& buffer)
{
    // Combine left and right channels into mono
    juce::AudioBuffer<float> monoBuffer(1, buffer.getNumSamples());
    monoBuffer.clear();

    auto* monoData = monoBuffer.getWritePointer(0);

    for (int ch = 0; ch < buffer.getNumChannels(); ++ch)
        monoBuffer.addFrom(0, 0, buffer, ch, 0, buffer.getNumSamples(), 0.5f); // average L+R

    visualiser.pushBuffer(monoBuffer);
}
