### Simple Oscillator Plugin
# By John Asper
A work-in-progress, simple, non-aliasing, Saw Wave oscillator plugin built using the JUCE Library/API.

Built in C++, and can be built into many different plugin types thanks to JUCE.

# Features
* Synthesized using a BandLimited Impulse Train, so it aliasing greatly reduced (Based on C code by Emmanuel Landeholm from 2002)
* Responds to MIDI note on and note off messages, including velocity
* No limit to the number of voices (as many as your processor can handle)
* Has an ADSR envelope (the times are fixed for now)

# TODO
* A GUI of any sort
* Adjustable envelope timings
* Filters
* More oscillator types


