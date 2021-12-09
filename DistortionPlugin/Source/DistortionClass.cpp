/*
  ==============================================================================

    DistortionClass.cpp
    Created: 4 Dec 2021 10:01:16am
    Author:  Matthew Williams

  ==============================================================================
*/

#include "DistortionClass.h"



float DistortionClass::softClipper(float input)
{
        if (input >= 0)
            return (sClipPosThresh / atan(posAlpha)) * atan(posAlpha * input);
        else if (input < 0)
            return (sClipNegThresh / atan(negAlpha)) * atan(negAlpha * input);
}

float DistortionClass::bitCrusher(float input)
{
        return round(input * crushSteps) * (1.0f / crushSteps);
}

float DistortionClass::waveFolder(float input)
{

    input = (input * foldDrive) + foldOffset;
    float fold1, fold2, fold3, fold4;
    /*
    if (input >= (-1 / folds) && input <= (1 / folds))          { return input; }    
    else if (input > (1 / folds) && input <= (2 / folds))       { return -input + (2 / folds); }
    else if (input > (2 / folds) && input <= (3 / folds))       { return input - (2 / folds); }
    else if (input > (3 / folds) && input <= (4 / folds))       { return -input + (4 / folds); }
    else if (input > (4 / folds) && input <= (5 / folds))       { return input - (4 / folds); }
    else if (input > (5 / folds) && input <= (6 / folds))       { return -input + (6 / folds); }
    else if (input > (6 / folds) && input <= (7 / folds))       { return input - (6 / folds); }
    else if (input > (7 / folds))                               { return -input + (8 / folds); }
    else if (input < (-1 / folds) && input >= (-2 / folds))     { return -input - (2 / folds); }
    else if (input < (-2 / folds) && input >= (-3 / folds))     { return input + (2 / folds); }
    else if (input < (-3 / folds) && input >= (-4 / folds))     { return -input - (4 / folds); }
    else if (input < (-4 / folds) && input >= (-5 / folds))     { return input + (4 / folds); }
    else if (input < (-5 / folds) && (input >= -6 / folds))     { return -input - (6 / folds); }
    else if (input < (-6 / folds) && input >= (-7 / folds))     { return input + (6 / folds); }
    else if (input < (-7 / folds)) { return -input - (8 / folds); }       
    */
    if (input > foldThresh)
        fold1 = -input + (2 * foldThresh);
    else if (input < -foldThresh)
        fold1 = -input - (2 * foldThresh);
    else return input;

    if (fold1 > foldThresh)
        fold2 = -fold1 + (2 * foldThresh);
    else if (fold1 < -foldThresh)
        fold2 = -fold1 - (2 * foldThresh);
    else return fold1;

    if (fold2 > foldThresh)
        fold3 = -fold2 + (2 * foldThresh);
    else if (fold2 < -foldThresh)
        fold3 = -fold2 - (2 * foldThresh);
    else return fold2;

    if (fold3 > foldThresh)
        return -fold3 + (2 * foldThresh);
    else if (fold3 < -foldThresh)
        return -fold3 - (2 * foldThresh);
    else return fold3;


}

float DistortionClass::distortionProcess(float input)
{

    float foldedSignal = foldOutGain * waveFolder((input * foldDrive) + foldOffset);
    float crushedSignal = bitCrusher(foldedSignal);
    float clippedSignal = sClipOutGain * softClipper(sClipInGain * input);
    return (wetDryMix(sClipMix) * ((crushMix * crushedSignal) + (wetDryMix(crushMix) * foldedSignal))) + (sClipMix * clippedSignal);
}

