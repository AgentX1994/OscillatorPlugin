/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>


//==============================================================================
OscillatorPluginAudioProcessor::OscillatorPluginAudioProcessor()
{
}

OscillatorPluginAudioProcessor::~OscillatorPluginAudioProcessor()
{
}

//==============================================================================
const String OscillatorPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OscillatorPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool OscillatorPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double OscillatorPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OscillatorPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int OscillatorPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OscillatorPluginAudioProcessor::setCurrentProgram (int index)
{
}

const String OscillatorPluginAudioProcessor::getProgramName (int index)
{
    return String();
}

void OscillatorPluginAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void OscillatorPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void OscillatorPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}


//double note_to_freq(int note) {
//    return 440.0*pow(2.0,(note-69.0)/12.0);
//}

void OscillatorPluginAudioProcessor::genSawWave(float *buffer, SawOscillator &v, int num_samples)
{
    for (int i = 0; i < num_samples; i++)
    {
        buffer[i] += v.next();
    }
}

void release_voice(std::vector<SawOscillator> &a, double freq)
{
    auto it = std::find_if(a.begin(), a.end(), [&freq](SawOscillator &v){return (v.getFreq() == freq) && !v.noteReleased(); });
    if (it != a.end()) {
        (*it).noteOff();
    }
}

void clear_finished_voices(std::vector<SawOscillator> &a)
{
    auto it = a.begin();
    while (it != a.end())
    {
        if ((*it).noteDone())
        {
            it = a.erase(it);
        } else {
            it++;
        }
    }
}

void OscillatorPluginAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    
    const int totalNumOutputChannels = getTotalNumOutputChannels();
    
    MidiBuffer::Iterator iterator(midiMessages);
    MidiMessage m;
    int sample_pos;
    while (iterator.getNextEvent(m, sample_pos)) {
        
            // Only care about note on and note off messages
        std::cout << m.getDescription() << std::endl;
        
        if (m.isNoteOn()) {
            double freq = m.getMidiNoteInHertz(m.getNoteNumber());
            voices.push_back(
                            //voice{freq, BLITSaw(0.5,0.0001),(double)m.getVelocity()/128}
                             SawOscillator(getSampleRate(), freq, (double)m.getVelocity()/128,
                                           att, dec, sus, rel)
                            );
        } else if (m.isNoteOff()) {
            release_voice(voices, m.getMidiNoteInHertz(m.getNoteNumber()));
        } else if (m.isAllNotesOff() || m.isAllSoundOff()) {
            voices.clear();
        }
    }
    midiMessages.clear(0, (int)m.getTimeStamp());
    
    clear_finished_voices(voices);

    float *channel_data;
    if (totalNumOutputChannels > 0) {
        channel_data = buffer.getWritePointer(0);
        buffer.clear(0, 0, buffer.getNumSamples());
        for (auto it = voices.begin(); it != voices.end(); it++)
        {
            if (!(*it).noteDone())
                genSawWave(channel_data, *it, buffer.getNumSamples());
            //else
                //it = voices.erase(it);
        }
    }
        // Copy the first channel to all other output channels
    for (int i = 1; i < totalNumOutputChannels; ++i)
    {
        buffer.copyFrom(i, 0, channel_data, buffer.getNumSamples());
    }
}

//==============================================================================
bool OscillatorPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* OscillatorPluginAudioProcessor::createEditor()
{
    return new OscillatorPluginProcessorEditor (*this);
}

//==============================================================================
void OscillatorPluginAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void OscillatorPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OscillatorPluginAudioProcessor();
}
