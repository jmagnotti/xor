#include "PointScale.h"


namespace XOR {

/**
 * Private default constructor
 */
PointScale::PointScale(void)
{

}


/**
 * Future scaleValues will use the following bounds
 */
PointScale::PointScale(float min, float max, float scaleDefault)
{

    _targetRange = max - min;
    _targetMin   = min;
    _scaleDefault = scaleDefault;
}


/**
 * Scales the given value from [min, max] to [target_min, target_max]
 */
float PointScale::scaleValue(float value, float min, float max)
{
    if (min == max)
        return _scaleDefault;

    float range = max - min;

    return ((value - min)/range) * _targetRange + _targetMin;
}


/**
 * Sets the bias factor. This value will be used when the range of the system
 * is 0.
 */ 
void PointScale::setScaleDefault(float scaleDefault)
{
    _scaleDefault = scaleDefault;
}


/**
 * Sets the range of the target system
 */
void PointScale::setSystemBounds(float min, float max)
{
    _targetMin   = min;
    _targetRange = max - min;
}


/**
 * Returns the value that is returned when the range of the target system is 0
 */
float PointScale::getScaleDefault()
{
    return _scaleDefault;
}


/**
 * Returns the base range of the scale
 */
float PointScale::getRange()
{
    return _targetRange;
}


/**
 * Returns the base value for the scale.
 */
float PointScale::getMin()
{
    return _targetMin;
}

}

