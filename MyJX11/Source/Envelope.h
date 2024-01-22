#pragma once

const float SILENCE = 0.0001f;

class Envelope{
public:
    float nextValue(){
        level *= multiplier;
        return level;
    }
    
    float level;
    float multiplier;
};
