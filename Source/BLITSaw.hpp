//
//  BLITSaw.hpp
//  OscillatorPlugin
//
//  Created by John Asper on 2017/9/20.
//

#ifndef BLITSaw_hpp
#define BLITSaw_hpp

#include <stdio.h>
#include <math.h>
#include "EnvelopeGenerator.hpp"

/*
 *  This class is an oscillator which creates a sawtooth wave
 *  using a band limited impulse train and a leaky integrator
 *
 *  A C++ class version of Emmanuel Landeholm's C version from 2002.
 */
class BLITSaw {
private:
    // Lowpass / Leaky Integrator variables
    double x1, y1;  // Previous sample input and output
    double lpa, lpb;    // Parameters
    
    // Lowpass / Leaky Integrator functions
    // initializes the lowpass filter parameters
    void init_lowpass(double cutoff);
    
    // Applies filter and updates parameters
    double update_lowpass(double x);
    
    // BLIT variables
    double phase;       // Phase accumulator
    double aNQ;         // Attenuation at nyquist frequency
    double curcps;      // Current frequency in this cycle
    double curper;      // Current period in this cycle
    double N;           // Number of Partials to keep
    double a;           // DSF parameter that controls roll off
    double aN;          // a to the Nth power
    
public:
    
    // Initialize the blit
    // aNQ = attenuation at nyquist
    // cutoff controls the leakiness of the integrator
    BLITSaw(double aNQ, double cutoff);
    
    double update_blit(double cps);
};

#endif /* BLITSaw_hpp */
