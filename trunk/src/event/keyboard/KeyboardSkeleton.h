#ifndef KEYBOARDSKELETON_H
#define KEYBOARDSKELETON_H


#include <stdlib.h>
#include <list>

#include "../../multicast/MulticastSocket.h"
#include "../../multicast/MulticastSocketPool.h"
#include "KeyboardListener.h"
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


private:

    KeyboardSkeleton();

    static KeyboardSkeleton * _keyboardSkeleton;

    MulticastSocket * _socket;

};

}

#endif			// KEYBOARDSKELETON_H

