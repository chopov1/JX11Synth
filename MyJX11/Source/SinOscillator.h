/*
  ==============================================================================

    SinOscillator.h
    Created: 13 Jan 2024 10:48:19pm
    Author:  chopo

  ==============================================================================
*/

#pragma once
#include <cmath>

//const float TWO_PI = 6.2831853071795864f;

class SinOscillator {
public:
    float amplitude;
    float inc;
    float phase;

    void reset() {
        //phase = 1.5707963268f;  //phase = TWO_PI / 4;
        phase = 0.0f;
        sin0 = amplitude * std::sin(phase * 6.2831853071795864f);
        sin1 = amplitude * std::sin((phase - inc) * 6.2831853071795864f);
        dsin = 2.0f * std::cos(inc * 6.2831853071795864f);
    }

    float nextSample() {
        /*phase += inc;
        if (phase >= 1.0f) {
            phase -= 1.0f;
        }
        return amplitude + sin(TWO_PI * phase);*/
        float sinx = dsin * sin0 - sin1;
        sin1 = sin0;
        sin0 = sinx;
        return sinx;
    }


private:
    float sin0;
    float sin1;
    float dsin;
};