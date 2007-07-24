#ifndef POINTSCALE_H
#define POINTSCALE_H


namespace XOR {

/**
 * Used to scale values from one system to another. Allows for setting a scale
 * default -- a value that will be returned when reference system has no range.
 */
class PointScale
{

public:

    /**
     * Future scaleValues will use the following bounds
     */
    PointScale(float min, float max, float scaleDefault);


    /**
     * Private default constructor
     */
    PointScale(void);


    /**
     * Returns the base value for the scale.
     */
    float getMin();


    /**
     * Returns the base range of the scale
     */
    float getRange();


    /**
     * Returns the value that is returned when the range of the target system is 0
     */
    float getScaleDefault();


    /**
     * Scales the given value from [min, max] to [target_min, target_max]
     */
    float scaleValue(float value, float min, float max);


    /**
     * Sets the bias factor. This value will be used when the range of the system
     * is 0.
     */ 
    void setScaleDefault(float scaleDefault);


    /**
     * Sets the range of the target system
     */
    void setSystemBounds(float min, float max);


private:

    float  _scaleDefault, _targetMin, _targetRange;

};

}

#endif			// POINTSCALE_H

