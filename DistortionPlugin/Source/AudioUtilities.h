
#pragma once
#include <math.h>

inline float wetDryMix (float input)
{
    return 1.0f - input;
}

inline float parameterSmooth(float input, float previousInput, float alpha = 0.95)
{
    return (1.0f - alpha) * input + alpha * previousInput;
}
