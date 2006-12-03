#include "MouseEventFactory.h"


namespace XOR {

MouseEvent * MouseEventFactory::_mouseEvent = 0;


/*
 * Factory constructor.
 */
MouseEvent * MouseEventFactory::ConstructInstance(SDL_Event * event)
{
    if (event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {

        //get the right button value
        const int * button;
        switch (event->button.button)
        {
            case SDL_BUTTON_LEFT:
                button = &(MouseClickEvent::LEFT_MOUSE_BUTTON);
                break;
            case SDL_BUTTON_MIDDLE:
                button = &(MouseClickEvent::MIDDLE_MOUSE_BUTTON);
                break;
            case SDL_BUTTON_RIGHT:
                button = &(MouseClickEvent::RIGHT_MOUSE_BUTTON);
                break;
            case SDL_BUTTON_WHEELUP:
                button = &(MouseClickEvent::MOUSE_WHEEL_UP);
                break;
            case SDL_BUTTON_WHEELDOWN:
                button = &(MouseClickEvent::MOUSE_WHEEL_DOWN);
                break;
            default:
                break;
        } 

        if (event->type == SDL_MOUSEBUTTONDOWN) {
            _mouseEvent =  new MouseButtonDown(button, &(event->button.x), &(event->button.y));
        }
        else if (event->type == SDL_MOUSEBUTTONUP) {
            _mouseEvent =  new MouseButtonUp(button, &(event->button.x), &(event->button.y));
        }
    }
    else {
        _mouseEvent =  new MouseMotionEvent(&(event->motion.x), &(event->motion.y),
                                    &(event->motion.xrel), &(event->motion.yrel));
    }

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

