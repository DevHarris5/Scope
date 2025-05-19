#include "PluginProcessor.h"
#include "PluginEditor.h"
ScopeAudioProcessorEditor::ScopeAudioProcessorEditor (ScopeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);
}

ScopeAudioProcessorEditor::~ScopeAudioProcessorEditor()
{
}

void ScopeAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void ScopeAudioProcessorEditor::resized()
{
}
