//
//  EnvelopeGenerator.hpp
//  OscillatorPlugin
//
//  Created by John Asper on 2017/9/26.
//

#ifndef EnvelopeGenerator_hpp
#define EnvelopeGenerator_hpp

#include <stdio.h>

typedef enum {
    OFF,
    ATTACK,
    DECAY,
    SUSTAIN,
    RELEASE
} ENV_STATE;

class EnvelopeGenerator {
private:
    ENV_STATE state;
    double time;            // Time since note on
    double curVal;          // Current gain
    
    double attackTime;      // Attack time in seconds
    double decayTime;       // Decay Time in seconds
    double sustainLevel;    // Sustain level (gain)
    double releaseTime;     // Release Time in seconds
    
    double sampleRate;      // Sample Rate in Hz
    double samplePeriod;    // Sample Period in seconds (1/sampleRate)
    
    double attackRate;      // Linear coefficient for attack stage
    double decayRate;       // Linear coefficient for decay stage;
    double releaseRate;     // Linear coefficient for release stage;
    
    void updateParams();    // Update parameters (coefficients, period
    void updateState();     // Update the state after getting sample
public:

    
    EnvelopeGenerator(double sr);
    EnvelopeGenerator(double sr, double attack, double decay, double sustain, double release);
    
    double next();          // Get next sample
    
    void release();         // Called when the midi note off is received
    double getCurVal() { return curVal; }
};
#endif /* EnvelopeGenerator_hpp */
