#ifndef FADEOUT_H
#define FADEOUT_H


#include "Transition.h"
#include "../paint/Paint.h"


/**
 * Interpolates a paint object from full alpha to 0 alpha
 */
class FadeOut : public Transition
{


public:

    /**
     * Explicit Constructor.
     * Initially uses 1/2 second for timing.
     */
    FadeOut(Paint * paint, int milliseconds = 500);


protected:

    Paint * _paint;
    int _time;

};


#endif          // FADEOUT_H

