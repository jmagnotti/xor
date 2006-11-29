#include "Fade.h"


Fade::Fade()
{
    // call the transition constructor to set the dimension
    Transition::Transition();
    _inTime = _outTime = 500;
}


Fade::Fade(int inTime, int outTime)
{
    // call the transition constructor to set the dimension
    Transition::Transition();

    _inTime  = inTime;
    _outTime = outTime;

    _fadeIn  = new FadeIn(_inTime);
    _fadeOut = new FadeOut(_outTime);
}


/*
 * This means that the fade out has been completed. Start the fade in. Notice 
 * that this is where we specify the original listener to be sued, since 
 * the completion of the FadeIn is the completion of the Fade transition
 */
void interpolationComplete()
{
    FadeIn::GetInstance(_inTime, _paint, _listener);
}

