#ifndef KEYBOARDSTUB_H
#define KEYBOARDSTUB_H


#include <stdlib.h>
#include <list>

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
class KeyboardStub : public Keyboard
{


public:

    /**
     * Singleton Accessor
     */
    static KeyboardStub * GetInstance();


	/**
	 * notify listeners of a  key event
	 */
	void fireKeyEvent(KeyEvent * ke);


private:

    KeyboardStub();
    static KeyboardStub * _keyboardStub;

    MulticastSocket * _socket;

};


}

#endif			// KEYBOARDSTUB_H

