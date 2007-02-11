#ifndef KEYBOARDSKELETON_H
#define KEYBOARDSKELETON_H


#include <stdlib.h>
#include <list>

#include "../../../include/SDL_thread.h"
#include "../../multicast/MulticastSocket.h"
#include "../../multicast/MulticastSocketPool.h"

#include "Keyboard.h"
#include "KeyEvent.h"
#include "KeyEventFactory.h"


using namespace std;

namespace XOR {

/**
 *
 */
class KeyboardSkeleton : public Keyboard
{

public:

    /**
     * Singleton Accessor
     */
    static KeyboardSkeleton * GetInstance();

	/**
	 * notify listeners of a  key event
	 */
	void fireKeyEvent(KeyEvent * ke);

	/**
	 * 
	 */
	static int Listen(void * data);


    ~KeyboardSkeleton();

private:

    KeyboardSkeleton();

	static bool _keepGoing;
    static KeyboardSkeleton * _keyboardSkeleton;

	SDL_Thread * _thread;

    static MulticastSocket * _socket;

};
}

#endif			// KEYBOARDSKELETON_H

