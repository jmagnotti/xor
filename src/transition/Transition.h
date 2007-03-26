#ifndef TRANSITION_H
#define TRANSITION_H


#include "../core/Viewer.h"


/**
 * Abstract parent class for Transitions.
 * This shouldn't be used instead of interpolators. In fact, this is kind of
 * a semantic grouping, and it allows for generic treatment of what we are
 * calling transitions. Work should be  done to make sure the transitions are
 * really sepearate from interpolators. One suggestion is to have transitions
 * lock keyboard input or something. 
 */
class Transition : public TimedInterpolator
{

public:

        Transition()
        {
            _size = Camera::GetInstance()->getWindowSize();
        }


protected:

    Dimension2D * _size;

};


#endif            // TRANSITION_H

