#ifndef FADEIN_H
#define FADEIN_H


#include "Transition.h"
#include "../paint/Paint.h"

/**
 * Interpolates a paint object from 0 alpha to full alpha
 */
class FadeIn : public Transition
{


public:


    /**
     * Because FadeIns are designed to be all-encompassing, there should 
     * only be one of them anyway.
     */
    FadeIn * GetInstance(int milliseconds = 500, Paint * p, 
                         InterpolationListener * listener);


protected:


    /**
     * Explicit Constructor.
     * Initially uses 1/2 second for timing.
     */
    FadeIn(Paint * paint, int milliseconds = 500);


    Paint * _paint;

private:

    FadeIn * _fadeIn;


};


#endif          // FADEIN_H

