#ifndef TRANSITIONFACTORY_H
#define TRANSITIONFACTORY_H


#include "Transition.h"
#include "Fade.h"
#include "FadeOut.h"
#include "FadeIn.h"


/**
 * Allows for the creation of Transitions.
 */
class TransitionFactory
{

    static const int FADE = 1;
    static const int FADE_IN = 2;
    static const int FADE_OUT = 3;

    static Transition * CreateTransition(int transitionType);

};


#endif          // TRANSITIONFACTORY_H

