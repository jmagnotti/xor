#ifndef MOUSEEVENTFACTORY_H
#define MOUSEEVENTFACTORY_H


#include "../../include/SDL.h"

#include "MouseEvent.h"
#include "MouseButtonDown.h"
#include "MouseButtonUp.h"
#include "MouseMotionEvent.h"


namespace XOR {


/**
 * Convenience class for constructing mouse events. Can take raw SDL_Events of 
 * MOUSEMOTION or MOUSEBUTTON. Soon should contain explicit constructors for non-SDL
 * events.
 */
class MouseEventFactory
{
    public:


        /**
         * Factory constructor
         */
        static MouseEvent * ConstructInstance(SDL_Event * event);


        /**
         * Returns the last event that was constructed by the factory. 
         * Here more for convenience than anything else.
         */
        static MouseEvent * getLastEventConstructed();


    protected:

        // no real need to create click factory, just a utility class
        MouseEventFactory();
 

    private:

        // stores the latest event
        static MouseEvent * _mouseEvent;

};

}

#endif          // MOUSEEVENTFACTORY_H
