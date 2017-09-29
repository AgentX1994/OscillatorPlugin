//
//  SawOscillator.cpp
//  OscillatorPlugin
//
//  Created by John Asper on 2017/9/26.
//

#include "SawOscillator.hpp"

SawOscillator::SawOscillator(double sr, double freq, double gain) :
    saw(0.5, 0.0001), env(sr), sampleRate(sr), freq(freq), gain(gain) {}

SawOscillator::SawOscillator(double sr, double freq, double gain, double att, double dec, double sus, double rel) :
    saw(0.5, 0.0001), env(sr, att, dec, sus, rel), sampleRate(sr), freq(freq), gain(gain) {}

double SawOscillator::next()
{
    return saw.update_blit(freq/sampleRate) * env.next() * gain;
}
