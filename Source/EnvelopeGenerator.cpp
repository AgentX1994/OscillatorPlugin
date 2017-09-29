//
//  EnvelopeGenerator.cpp
//  OscillatorPlugin
//
//  Created by John Asper on 2017/9/26.
//

#include "EnvelopeGenerator.hpp"

EnvelopeGenerator::EnvelopeGenerator(double sr)
{
    state = ATTACK;
    time = 0.0;
    
    attackTime = 0.25;
    decayTime = 0.5;
    sustainLevel = 0.75;
    releaseTime = 0.25;
    
    sampleRate = sr;
    
    updateParams();
}

EnvelopeGenerator::EnvelopeGenerator(double sr, double attack, double decay, double sustain, double release)
{
    state = ATTACK;
    time = 0.0;
    
    attackTime = attack;
    decayTime = decay;
    sustainLevel = sustain;
    releaseTime = release;
    
    sampleRate = sr;
    updateParams();
}

void EnvelopeGenerator::updateParams()
{
    curVal = 0.0;
    samplePeriod = 1.0/sampleRate;
    
    attackRate  = 1.0/attackTime;
    decayRate   = (sustainLevel - 1.0)/decayTime;
}

void EnvelopeGenerator::release()
{
    state = RELEASE;
    releaseRate = curVal/releaseTime;
}

void EnvelopeGenerator::updateState()
{
    if (state == OFF) return;
    
    time += samplePeriod;
    switch (state) {
        case OFF:
            break;
        case SUSTAIN:
            curVal = sustainLevel;
            break;
        case ATTACK:
            curVal += attackRate*samplePeriod;
            if (time >= attackTime) {
                state = DECAY;
                time -= attackTime;
                curVal = 1;
            }
            break;
        case DECAY:
            curVal -= decayRate * samplePeriod;
            if (time >= decayTime) {
                time -= decayTime;
                state = SUSTAIN;
                curVal = sustainLevel;
            }
            break;
        case RELEASE:
            curVal -= releaseRate * samplePeriod;
            break;
    }
}

double EnvelopeGenerator::next()
{
    double value;
    switch (state) {
        case OFF:
            value = 0.0;
            break;
        case ATTACK:
        case DECAY:
        case RELEASE:
            value = curVal;
            break;
        case SUSTAIN:
            value = sustainLevel;
            break;
    }
    updateState();
    return value;
}
