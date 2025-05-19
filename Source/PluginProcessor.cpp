#include "PluginProcessor.h"
#include "PluginEditor.h"

ScopeAudioProcessor::ScopeAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
        .withOutput("Output", juce::AudioChannelSet::stereo(), true))
#endif
{
    std::fill(std::begin(circularBuffer), std::end(circularBuffer), 0.0f);
}

ScopeAudioProcessor::~ScopeAudioProcessor() {}

const juce::String ScopeAudioProcessor::getName() const { return JucePlugin_Name; }

bool ScopeAudioProcessor::acceptsMidi() const { return false; }
bool ScopeAudioProcessor::producesMidi() const { return false; }
bool ScopeAudioProcessor::isMidiEffect() const { return false; }
double ScopeAudioProcessor::getTailLengthSeconds() const { return 0.0; }

int ScopeAudioProcessor::getNumPrograms() { return 1; }
int ScopeAudioProcessor::getCurrentProgram() { return 0; }
void ScopeAudioProcessor::setCurrentProgram(int index) {}
const juce::String ScopeAudioProcessor::getProgramName(int index) { return {}; }
void ScopeAudioProcessor::changeProgramName(int index, const juce::String& newName) {}

void ScopeAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {}
void ScopeAudioProcessor::releaseResources() {}

void ScopeAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer&) {
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
        auto* channelData = buffer.getReadPointer(channel);

        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            circularBuffer[writeIndex] = channelData[i];
            writeIndex = (writeIndex + 1) % bufferSize;
        }
    }
}

bool ScopeAudioProcessor::hasEditor() const { return true; }
juce::AudioProcessorEditor* ScopeAudioProcessor::createEditor() {
    return new ScopeAudioProcessorEditor(*this);
}

void ScopeAudioProcessor::getStateInformation(juce::MemoryBlock& destData) {}
void ScopeAudioProcessor::setStateInformation(const void* data, int sizeInBytes) {}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ScopeAudioProcessor();
}
