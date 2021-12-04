/*
  ==============================================================================

    DistortionClass.h
    Created: 4 Dec 2021 10:01:16am
    Author:  Matthew Williams

  ==============================================================================
*/

#pragma once
#include <cmath>

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
    float folds;
    float foldDrive = 0.0f, foldOutGain, foldOffset;

public:
    float distortionProcess(float input);

    float getRectInGain()               { return rectInGain; }
    float getRectThresh()               { return rectThresh; }
    float getRectOutGain()              { return rectOutGain; }

    void setRectInGain(float newVal)    { rectInGain = newVal; }
    void setRectThresh(float newVal)    { rectThresh = newVal; }
    void setRectOutGain(float newVal)   { rectOutGain = newVal; }

    float getSClipInGain()              { return sClipInGain; }
    float getPosAlpha()                 { return posAlpha; }
    float getSClipPosThresh()           { return sClipPosThresh; }
    float getNegAlpha()                 { return negAlpha; }
    float getSClipNegThresh()           { return sClipNegThresh; }
    float getSClipOutGain()             { return sClipOutGain; }

    void setSClipInGain(float newVal)   { sClipInGain = newVal; }
    void setPosAlpha(float newVal)      { posAlpha = newVal; }
    void setSClipPosThresh(float newVal){ sClipPosThresh = newVal; }
    void setNegAlpha(float newVal)      { negAlpha = newVal; }
    void setSClipNegThresh(float newVal){ sClipNegThresh = newVal; }
    void setSClipOutGain(float newVal)  { sClipOutGain = newVal; }

    float getCrushSteps()               { return crushSteps; }
    bool getCrushBypass()               { return crushBypass; }

    void setCrushSteps(float newVal)    { crushSteps = newVal; }
    void setCrushBypass(bool newBool)   { crushBypass = newBool; }

    float getFoldDrive()               { return foldDrive; }
    float getFoldOutGain()              { return foldOutGain; }
    float getFolds()                    { return folds; }
    float getFoldOffset()               { return foldOffset; }

    void setFoldDrive(float newVal)    { foldDrive = newVal; }
    void setFoldOutGain(float newVal)   { foldOutGain = newVal; }
    void setFolds(float newVal)         { folds = newVal; }
    void setFoldOffset(float newVal)    { foldOffset = newVal; }



};