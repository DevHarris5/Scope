#include "PluginProcessor.h"
#include "PluginEditor.h"

ScopeAudioProcessor::ScopeAudioProcessor()
    : AudioProcessor(BusesProperties()
        .withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
}

ScopeAudioProcessor::~ScopeAudioProcessor() {}

const juce::String ScopeAudioProcessor::getName() const { return JucePlugin_Name; }

bool ScopeAudioProcessor::acceptsMidi() const { return false; }
bool ScopeAudioProcessor::producesMidi() const { return false; }
bool ScopeAudioProcessor::isMidiEffect() const { return false; }
double ScopeAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int ScopeAudioProcessor::getNumPrograms() { return 1; }
int ScopeAudioProcessor::getCurrentProgram() { return 0; }
void ScopeAudioProcessor::setCurrentProgram(int) {}
const juce::String ScopeAudioProcessor::getProgramName(int) { return {}; }
void ScopeAudioProcessor::changeProgramName(int, const juce::String&) {}

void ScopeAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    juce::ignoreUnused(sampleRate, samplesPerBlock);
}

void ScopeAudioProcessor::releaseResources() {}

void ScopeAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
    juce::ScopedNoDenormals noDenormals;

    if (auto* editor = dynamic_cast<ScopeAudioProcessorEditor*>(getActiveEditor()))
        editor->pushBuffer(buffer);
}

bool ScopeAudioProcessor::hasEditor() const { return true; }

juce::AudioProcessorEditor* ScopeAudioProcessor::createEditor() {
    return new ScopeAudioProcessorEditor(*this);
}

void ScopeAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {
    // Save state here
}

void ScopeAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {
    // Restore state here
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ScopeAudioProcessor();
}

