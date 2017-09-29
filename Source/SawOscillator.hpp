//
//  SawOscillator.hpp
//  OscillatorPlugin
//
//  Created by John Asper on 2017/9/26.
//

#ifndef SawOscillator_hpp
#define SawOscillator_hpp

#include <stdio.h>
#include "BLITSaw.hpp"
#include "EnvelopeGenerator.hpp"

class SawOscillator
{
private:
    BLITSaw saw;                 // saw wave generator
    EnvelopeGenerator env;       // Envelope generator
    double sampleRate;          // Sample Rate
    double freq;                // frequency of this saw wave
    double gain;                // the amplitude of this saw wave
    bool done = false;          // Done playing?
    
public:
    SawOscillator(double sampleRate, double frequency, double gain);
    SawOscillator(double sampleRate,
                  double frequency,
                  double gain,
                  double attack,
                  double decay,
                  double sustain,
                  double release);
    
    double getFreq() { return freq; }
    double getGain() { return gain; }
    
    void setFreq(double f) { freq = f; }
    void setGain(double g) { gain = g; }
    
    // Get next sample
    double next();
    
    void noteOff() { env.release(); done = true; }
    bool noteReleased() { return done; }
    bool noteDone() { return done && (env.getCurVal() < 0.01); }
};
#endif /* SawOscillator_hpp */
