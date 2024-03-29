/*
  ==============================================================================

    Voice.h
    Created: 10 Jan 2024 1:52:44pm
    Author:  chopo

  ==============================================================================
*/

#pragma once
#include "Oscillator.h"
#include "SinOscillator.h"
#include "Envelope.h"

struct Voice {

    Oscillator osc;
    Envelope env;

    int note;
    float saw;

    void reset() {
        saw = 0.0f;
        note = 0;
        osc.reset();
    }

    float render(float input) {
        float sample = osc.nextSample();
        saw = saw * 0.997f - sample;
        
        float output = saw + input;
        
        float envelope = env.nextValue();
        return output * envelope;
    }
};

struct SinVoice {
    SinOscillator osc;

    int note;

    void reset() {
        note = 0;
        osc.reset();
    }

    float render() {
        return osc.nextSample();
    }
};
