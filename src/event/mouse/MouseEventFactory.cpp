#include "MouseEventFactory.h"


namespace XOR {

MouseEvent * MouseEventFactory::_mouseEvent = 0;


/*
 * Factory constructor.
 */
MouseEvent * MouseEventFactory::ConstructInstance(SDL_Event * event)
{
    if (event->type == SDL_MOUSEMOTION)
        _mouseEvent =  new MouseMotionEvent(event->motion.x, event->motion.y,
                                    event->motion.xrel, event->motion.yrel);

    else if (event->type == SDL_MOUSEBUTTONDOWN)
        _mouseEvent =  new MouseButtonDown(event->button.button,
                event->button.x, event->button.y);
    else 
        _mouseEvent =  new MouseButtonUp(event->button.button, event->button.x,
                event->button.y);

    return _mouseEvent;
}


/*
 * Returns the last event that was constructed by the factory. Here more for 
 * convenience than anything else. If there hasn't been a last event, NULL is _mouseEvent = ed.
 */
MouseEvent * MouseEventFactory::getLastEventConstructed()
{
    return  _mouseEvent;
}


/*
 * no real need to create click factory, just a utility class
 */
MouseEventFactory::MouseEventFactory()
{}


}

