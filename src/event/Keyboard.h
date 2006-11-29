#ifndef KEYBOARD_H
#define KEYBOARD_H


#include <stdlib.h>
#include <vector>

#include "KeyboardListener.h"
#include "RegularKeyEvent.h"
#include "SpecialKeyEvent.h"


using namespace std;

namespace XOR {

/**
 * Defines a keyboard that generates key press events
 * Does not maintain state information, unlike Mouse.cpp
 */
class Keyboard
{

private:
    vector <KeyboardListener*> listeners;


public:


    /**
     * Singleton accessor
     */
    Keyboard * GetInstance();    


	/**
	 * Add a listener
	 */
	void addListener(KeyboardListener* kl);


	/**
	 * Removes a listener
	 */
	void removeListener(KeyboardListener* kl);


    /**
     * turn an sdl event into a key event
     */
    void generateKeyEvent(SDL_Event * event);
    

	/**
	 * notify listeners of a special key event
	 */
	void specialKeyEvent(int key, int x, int y);


	/**
	 * notify listeners of a regular key event
	 */
	void regularKeyEvent(unsigned char key, int x, int y);


protected:

	Keyboard()
    {}

public:

    Keyboard * _keyboard;

};

}

#endif			// KEYBOARD_H

