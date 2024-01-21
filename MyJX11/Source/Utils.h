/*
  ==============================================================================

    Utils.h
    Created: 10 Jan 2024 3:29:17pm
    Author:  chopo

  ==============================================================================
*/

#pragma once

#include <cmath>
#include <JuceHeader.h>

inline void protectYourEars(float* buffer, int samplecount) {
    if (buffer == nullptr) { return; };
    bool firstWarning = true;
    for (int i = 0; i < samplecount; ++i) {
        float x = buffer[i];
        bool silence = false;
        if (std::isnan(x)) {
            DBG("!!!WARNING: nan detected in audio buffer, silencing !!!");
            silence = true;
        }
        else if (std::isinf(x)) {
            DBG("!!!WARNING: inf detected in audio buffer, silencing !!!");
            silence = true;
        }
        else if (x < -2.0f || x > 2.0f) {
            //screaming feedback
            DBG("!!!WARNING: sample out of range, silencing !!!");
            silence = true;
        }
        else if (x < -1.0f) {
            if (firstWarning) {
                DBG("!!! WARNING: sample out of range, clamping !!!");
                firstWarning = false;
            }
            buffer[i] = -1.0f;
        }
        else if (x > 1.0f) {
            if (firstWarning) {
                DBG("!!! WARNING: sample out of range, clamping !!!");
                firstWarning = false;
            }
            buffer[i] = 1.0f;
        }
        if (silence) {
            memset(buffer, 0, samplecount + sizeof(float));
            return;
        }
    }
}