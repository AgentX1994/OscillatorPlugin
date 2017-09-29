//
//  BLITSaw.cpp
//  OscillatorPlugin
//
//  Created by John Asper on 2017/9/20.
//

#include "BLITSaw.hpp"

BLITSaw::BLITSaw(double aNQ, double cutoff) :
phase(0.0), aNQ(aNQ), curcps(0.0), curper(0.0)
{
    init_lowpass(cutoff);
}

void BLITSaw::init_lowpass(double cutoff)
{
    double omega;
    
    x1 = y1 = 0;
    lpb = 0.0;
    
    omega = atan(M_PI * cutoff);
    lpa = -(1.0 - omega) / (1.0 + omega);
    lpb = (1.0 - lpb) / 2.0;
}

double BLITSaw::update_lowpass(double x)
{
    double y;
    
    y = lpb * (x + x1) - lpa * y1;
    
    x1 = x;
    y1 = y;
    
    return y;
}

double BLITSaw::update_blit(double cps)
{
    if (phase >= 1.0 || curcps == 0.0)
    {
        // New Cycle, update parameters
        
        if (phase >= 1.0) phase -= 1.0;
        
        curcps = cps;       // This cycle's freq
        curper = 1.0/cps;   // This cycle's period
        
        double p2 = curper / 2.0; // half a period
        N = 1 + floor(p2);          // Number of partials including dc
        
        // Find the correct roll off parameter to give the desired
        // Nyquist attenuation
        a = pow(aNQ, 1.0/p2);
        aN = pow(a, N);
    }
    
    double beta = 2 * M_PI * phase;
    double Nbeta = N * beta;
    double cosbeta = cos(beta);
    
    // The dsf blit is scaled by 1/period to give approximately the
    // same peak-to-peak amplitude at a wide variety of frequencies
    double n = 1.0 - \
        aN * cos(Nbeta) - \
        a * (cosbeta - aN * cos(Nbeta - beta));
    double d = curper * (1.0 + a * (-2.0 * cosbeta + a));
    
    phase += curcps; // Update phase
    
    // This division can only fail if |a| = 1
    // Subtracting curcps gets rid of DC
    double blit = n / d - curcps;
    
    double saw = update_lowpass(blit); /* shape into a saw */
    
    return saw;
}
