/*
  ==============================================================================

    DistortionClass.h
    Created: 4 Dec 2021 10:01:16am
    Author:  Matthew Williams

  ==============================================================================
*/

#pragma once

class DistortionClass
{
private:
    float halfRectifier(float input);
    float fullRectifier(float input);
    float softClipper(float input);
    float bitCrusher(float input);
    float waveFolder(float input);
    float rectInGain, rectThresh, rectOutGain;
    float sClipInGain, posAlpha, sClipPosThresh, negAlpha, sClipNegThresh, sClipOutGain;
    float crushSteps;
    bool crushBypass;
    float foldInGain, foldOutGain, folds, foldOffset;

public:
    float distortionProcess(float input);
};