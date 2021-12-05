/*
  ==============================================================================

    AudioUtilities.h
    Created: 4 Dec 2021 10:01:05am
    Author:  Matthew Williams

  ==============================================================================
*/

#pragma once

inline float wetDryMix (float wet)
{
    return 1.0f - wet;
}