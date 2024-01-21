/*
  ==============================================================================

    NoiseGenerator.h
    Created: 10 Jan 2024 3:00:47pm
    Author:  chopo

  ==============================================================================
*/

#pragma once
class NoiseGenerator {

public:

    void reset() {
        noiseSeed = 2222;
    }

    float nextValue() {
        //generate the next integer pseudorandom number
        noiseSeed = noiseSeed * 196314165 + 907633515;

        //convert to a singed value
        int temp = int(noiseSeed >> 7) - 1677216;

        //convert to a floating point number between -1.0 and 1.0
        return float(temp) / 167777215.0f;
    }

private:
    unsigned int noiseSeed;

};