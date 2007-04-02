#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <stdlib.h>
#include <list>

#include <SDL/SDL.h>

#include "KeyboardListener.h"
#include "KeyEvent.h"
#include "KeyEventFactory.h"


using namespace std;

namespace XOR {


/**
 * Defines a keyboard that generates key press events. Check out
 * KeyboardSkeleton for implementation details.
 * Does not maintain state information, unlike Mouse.cpp
 */
class Keyboard
{


public:

	/**
	 * Add a listener
	 */
	void addListener(KeyboardListener * kl);


	/**
	 * Removes a listener
	 */
	void removeListener(KeyboardListener * kl);


    /**
     * turn an sdl event into a key event
     */
    void generateKeyEvent(SDL_Event * event);


    /**
     * Access to the SDL Event queue
     */
    static void FireSDLEvent(SDL_Event * event);
    

	/**
	 * notify listeners of a  key event
	 */
	virtual void fireKeyEvent(KeyEvent * ke)=0;


protected:

    /**
     * Tell all listeners in the pool that a keyboard event has fired
     */
    void notifyListeners(KeyEvent * ke);

    static const unsigned short PORT;
    static const char * GROUP;

    list <KeyboardListener*> _listeners;

};

}

#endif			// KEYBOARD_H

