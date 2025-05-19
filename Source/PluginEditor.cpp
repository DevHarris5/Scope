#include "PluginProcessor.h"
#include "PluginEditor.h"

ScopeAudioProcessorEditor::ScopeAudioProcessorEditor(juce::AudioProcessor& p)
    : AudioProcessorEditor(&p), visualiser(2) // stereo
{
    setSize(600, 400);

    visualiser.setBufferSize(128);
    visualiser.setSamplesPerBlock(16);
    visualiser.setColours(juce::Colours::black, juce::Colours::lime);
    visualiser.setRepaintRate(60);

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
    visualiser.pushBuffer(buffer);
}
