/*
  ==============================================================================

    Synth.cpp
    Created: 10 Jan 2024 1:52:39pm
    Author:  chopo

  ==============================================================================
*/

#include "Synth.h"
#include "Utils.h"

Synth::Synth()
{
    sampleRate = 441000;
}

void Synth::allocateResources(double sampleRate_, int samplesPerBlock)
{
    sampleRate = static_cast<float>(sampleRate_);
}

void Synth::deallocateResources()
{
    
}

void Synth::reset()
{
    voice.reset();
    noiseGen.reset();
}

void Synth::render(float** outputBuffers, int sampleCount)
{
    float* outputBufferLeft = outputBuffers[0];
    float* outputBufferRight = outputBuffers[1];

    //1
    for (int sample = 0; sample < sampleCount; ++sample) {
        //2
        float noise = noiseGen.nextValue();

        //3
        float output = 0.0f;
        if (voice.note > 0) {
            output = voice.render();
            output += sinVoice.render();
            //output = noise * (voice.velocity / 127.0f) * 0.5f; //4
            //output = 0.6 * sin(2 * 3.14 * sampleCount * 440 / sampleRate);
        }

        //5
        outputBufferLeft[sample] = output;
        if (outputBufferRight != nullptr) {
            outputBufferRight[sample] = output;
        }

    }
    protectYourEars(outputBufferLeft, sampleCount);
    protectYourEars(outputBufferRight, sampleCount);
}

void Synth::midiMessages(uint8_t data0, uint8_t data1, uint8_t data2)
{
    switch (data0 & 0xF0) {
        //note off
        case 0x80:
            noteOff(data1 & 0x7F);
            break;
        //note on
        case 0x90: {
            uint8_t note = data1 & 0x7F;
            uint8_t velo = data2 & 0x7F;
            if (velo > 0) {
                noteOn(note, velo);
            }
            else {
                noteOff(note);
            }
            break;
        }
    }
}

void Synth::noteOn(int note, int velocity)
{
    voice.note = note;

    sinVoice.note = note;
    
    float freq = 440.0f * exp2(float(note - 69) / 12.0f);;

    voice.osc.amplitude = (velocity / 127.0f) * 0.5f;
    voice.osc.period = sampleRate / freq;
    voice.osc.reset();

    sinVoice.osc.amplitude = (velocity / 127.0f) * 0.5f;
    sinVoice.osc.inc = freq / sampleRate;
    sinVoice.osc.reset();
}

void Synth::noteOff(int note)
{
    if (voice.note == note) {
        voice.note = 0;
    }

    if (sinVoice.note == note) {
        sinVoice.note = 0;
    }
}
