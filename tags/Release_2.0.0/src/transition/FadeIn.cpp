#include "FadeIn.h"


// set the static instance to 0;
FadeIn::_fadeIn = 0;


/*
 * Singleton Accessor
 */
FadeIn * FadeIn::GetInstance()
{
    if (_fadeIn == 0)
        _fadeIn = new FadeIn();

    return _fadeIn;
}


/*
 * Singleton Accessor
 */
FadeIn * FadeIn::GetInstance(int milliseconds, Paint * paint, 
                             InterpolationListener * listener)
{
    if (_fadeIn == 0) {
        _fadeIn = new FadeIn(milliseconds, paint, listener);
    }
    else {
        _time = milliseconds;
        
        // we need to recalculate the interpolator
        delete _paint;
        _paint = paint;

        addListener(listener);

        setup();
    }

    return _fadeIn;
}


/*
 * Protected Constructor
 */
FadeIn::FadeIn(int milliseconds, Paint * paint, InterpolationListener * listener)
{
    _time = milliseconds;
    _paint = paint;
    addListener(listener);

    setup();
}


/*
 * Protected Constructor
 */
FadeIn::FadeIn()
{
    _paint = new Paint(Color::BLACK);
    _time = 500;

    setup();
}


/*
 * Protected constructor
 */
FadeIn::FadeIn(Paint * paint, int milliseconds)
{
    _paint = paint;
    _time = milliseconds;

    setup();
}

