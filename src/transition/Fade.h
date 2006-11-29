#ifndef FADE_H
#define FADE_H


#include "../interpolation/InterpolationListener.h"
#include "../geometry/Dimension2D.h"
#include "../paint/Paint.h"
#include "../paint/Color.h"
#include "Transition.h"


/**
 * Encapsulates both Fade in and fade out.
 * Allows for specification of both the fade in & out time. Currently the fade
 * always uses a quad over a portion (including all of it) of the screen.
 * The interpolating part is accomplished by a paint object -- note that this
 * allows for texture fading -- more work probably has to be done for that to
 * work properly though.
 */
class Fade : public InterpolationListener, public Transition
{

    /**
     *
     */
    Fade();


    /**
     *
     */
    Fade(int inTime = 500, int outTime = 500, Paint * p = new Paint(Color::BLACK);


    /**
     * Used so it knows when to start the fade in after first fading out.
     */
    void interpolationComplete();


protected:

    int _inTime, _outTime;

    FadeIn  * _fadeIn;
    FadeOut * _fadeOut;

};


#endif          // FADE_H

