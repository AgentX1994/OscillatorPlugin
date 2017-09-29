/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <sstream>

//==============================================================================
OscillatorPluginProcessorEditor::OscillatorPluginProcessorEditor (OscillatorPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    startTimer(1.0/60.0);
}

OscillatorPluginProcessorEditor::~OscillatorPluginProcessorEditor()
{
}

void OscillatorPluginProcessorEditor::timerCallback() {
    repaint();
}

//==============================================================================
void OscillatorPluginProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (15.0f);
    
    std::stringstream ss;
    ss << "Current Voices:" << std::endl;
    for (auto v : processor.voices) {
        ss << "\tFrequency: " << v.getFreq() << std::endl;
    }
    g.drawFittedText (ss.str(), getLocalBounds(), Justification::centred, 1);
}

void OscillatorPluginProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
