#include "TransitionFactory.h"


/*
 * Returns a transition
 */
Transition * TransitionFactory::CreateTransition(int transitionType)
{

    switch (transitionType) {
        case FADE:
            return new Fade();
            break;
        case FADE_IN:
            return new FadeIn();
            break;
        case FADE_OUT:
            return new FadeOut();
            break;
        default:
            return new Transition();
            break;
    }

}


