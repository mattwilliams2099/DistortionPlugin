/*
  ==============================================================================

    AudioUtilities.h
    Created: 4 Dec 2021 10:01:05am
    Author:  Matthew Williams

  ==============================================================================
*/

#pragma once

inline float wetDryMix (float input)
{
    return 1.0f - input;
}


inline float parameterSmooth(float input, float previousInput, float alpha = 0.95)
{
    return (1.0f - alpha) * input + alpha * previousInput;
}