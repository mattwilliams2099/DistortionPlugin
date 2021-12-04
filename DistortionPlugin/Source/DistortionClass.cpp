/*
  ==============================================================================

    DistortionClass.cpp
    Created: 4 Dec 2021 10:01:16am
    Author:  Matthew Williams

  ==============================================================================
*/

#include "DistortionClass.h"

float DistortionClass::halfRectifier(float input)
{
    if (input < rectThresh)
        return rectThresh;
    else
        return input;
}

float DistortionClass::fullRectifier(float input)
{
    if (input < rectThresh)
        return rectThresh + ((-input) + rectThresh);
    else
        return input;
}

float DistortionClass::softClipper(float input)
{
    return (sClipPosThresh / atan(posAlpha)) * atan(posAlpha * input);
}

float DistortionClass::bitCrusher(float input)
{
        return round(input * crushSteps) * (1 / crushSteps);

}

float DistortionClass::waveFolder(float input)
{
    if (input >= 0 && input <= (1 / folds))
        return input;
    else if (input > (1 / folds) && (input <= (2 / folds)))
        return ((1 / folds) - (input - (1 / folds)));
    else if (input > (2 / folds) && (input <= (3 / folds)))
        return ((input - (2 / folds)));
    else if (input > (3 / folds) && (input <= (4 / folds)))
        return ((1 / folds) - (input - (3 / folds)));
    else if (input > (4 / folds) && (input <= (5 / folds)))
        return ((input - (4 / folds)));
    else if (input > (5 / folds) && (input <= (6 / folds)))
        return ((1 / folds) - (input - (5 / folds)));
    else if (input > (6 / folds) && (input <= (7 / folds)))
        return ((input - (6 / folds)));
    else if (input > (7 / folds))
        return ((1 / folds) - (input - (7 / folds)));
    else if (input < 0 && (input >= (-1 / folds)))
        return input;
    else if (input < (-1 / folds) && (input >= (-2 / folds)))
        return ((-(1 / folds)) - (input + (1 / folds)));
    else if (input < (-2 / folds) && (input >= (-3 / folds)))
        return ((input + (2 / folds)));
    else if (input < (-3 / folds) && (input >= (-4 / folds)))
        return ((-1 / folds) - (input + (3 / folds)));
    else if (input < (-4 / folds) && (input >= (-5 / folds)))
        return ((input + (4 / folds)));
    else if (input < (-5 / folds) && (input >= (-6 / folds)))
        return ((-1 / folds) - (input + (5 / folds)));
    else if (input < (-6 / folds) && (input >= (-7 / folds)))
        return ((input + (6 / folds)));
    else if (input < (-7 / folds))
        return ((-1 / folds) - (input + (7 / folds)));
}

