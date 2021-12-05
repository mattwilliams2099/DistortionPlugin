/*
  ==============================================================================

    DistortionClass.h
    Created: 4 Dec 2021 10:01:16am
    Author:  Matthew Williams

  ==============================================================================
*/

#pragma once
#include <cmath>
#include "AudioUtilities.h"

class DistortionClass
{
private:
    float softClipper(float input);
    float bitCrusher(float input);
    float waveFolder(float input);
    float rectInGain, rectThresh, rectOutGain;
    float sClipInGain, posAlpha, sClipPosThresh, negAlpha, sClipNegThresh, sClipOutGain;
    float crushSteps;
    bool crushBypass, symmetryToggle;
    float folds;
    float foldDrive = 0.0f, foldOutGain, foldOffset;
    float crushMix, sClipMix;

public:
    float distortionProcess(float input);

    float getSClipInGain()              { return sClipInGain; }
    float getPosAlpha()                 { return posAlpha; }
    float getSClipPosThresh()           { return sClipPosThresh; }
    float getNegAlpha()                 { return negAlpha; }
    float getSClipNegThresh()           { return sClipNegThresh; }
    float getSClipOutGain()             { return sClipOutGain; }

    void setSClipInGain(float newVal)   { sClipInGain = newVal; }
    void setPosAlpha(float newVal) 
    {
        posAlpha = newVal;
        if (symmetryToggle == true) negAlpha = posAlpha;
    }
    void setSClipPosThresh(float newVal)
    { 
        sClipPosThresh = newVal;
        if (symmetryToggle == true) sClipNegThresh = sClipPosThresh;
    }
    void setNegAlpha(float newVal)      { negAlpha = newVal; }
    void setSClipNegThresh(float newVal){ sClipNegThresh = newVal; }
    void setSClipOutGain(float newVal)  { sClipOutGain = newVal; }

    float getCrushSteps()               { return crushSteps; }
    bool getsymmetryToggle()               { return symmetryToggle; }

    void setCrushSteps(float newVal)    { crushSteps = newVal; }
    void setSymmetryToggle(bool newBool)   { symmetryToggle = newBool; }

    float getFoldDrive()               { return foldDrive; }
    float getFoldOutGain()              { return foldOutGain; }
    float getFolds()                    { return folds; }
    float getFoldOffset()               { return foldOffset; }

    void setFoldDrive(float newVal)    { foldDrive = newVal; }
    void setFoldOutGain(float newVal)   { foldOutGain = newVal; }
    void setFolds(float newVal)         { folds = newVal; }
    void setFoldOffset(float newVal)    { foldOffset = newVal; }

    void setCrushMix(float newVal) {
        crushMix = newVal;
    }
    void setMix(float newVal) {
        sClipMix = newVal;
    }
};