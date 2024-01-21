/*
  ==============================================================================

    Synth.h
    Created: 10 Jan 2024 1:52:33pm
    Author:  chopo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Voice.h"
#include "NoiseGenerator.h"

class Synth {

public:

    Synth();

    void allocateResources(double sampleRate_, int samplesPerBlock);
    void deallocateResources();
    void reset();
    void render(float** outputbuffers, int sampleCount);
    void midiMessages(uint8_t data0, uint8_t data1, uint8_t data2);


private:

    void noteOn(int note, int velocity);
    void noteOff(int note);

    float sampleRate;
    Voice voice;
    SinVoice sinVoice;
    NoiseGenerator noiseGen;
};