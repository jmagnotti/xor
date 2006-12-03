#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <stdlib.h>
#include <list>

#include "KeyboardListener.h"
#include "KeyEvent.h"
#include "KeyEventFactory.h"


using namespace std;

namespace XOR {

//we need to forward declare keyboardlistener
class KeyboardListener;

/**
 * Defines a keyboard that generates key press events
 * Does not maintain state information, unlike Mouse.cpp
 */
class Keyboard
{


public:


    /**
     * Singleton accessor
     */
    static Keyboard * GetInstance();    


	/**
	 * Add a listener
	 */
	void addListener(KeyboardListener * kl);


	/**
	 * Removes a listener
	 */
	void removeListener(KeyboardListener* kl);


    /**
     * turn an sdl event into a key event
     */
    void generateKeyEvent(SDL_Event * event);
    

	/**
	 * notify listeners of a  key event
	 */
	void fireKeyEvent(KeyEvent * ke);


protected:

    list <KeyboardListener*> _listeners;


private:

    static Keyboard * _keyboard;

};

}

#endif			// KEYBOARD_H

