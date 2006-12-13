#ifndef DEFAULTKEYBOARDLISTENER_H
#define DEFAULTKEYBOARDLISTENER_H

#include <map>

#include "KeyboardListener.h"
#include "KeyEvent.h"
#include "../core/Controller.h"
#include "../core/World.h"


namespace XOR {

/** 
 * Represents the default key event behavior. Methods are purposely made virtual to allow
 * people to easily extend this classes behavior.
 */
class DefaultKeyboardListener : public KeyboardListener
{

public:


	/**
	 * Singleton Accessor
	 */
	static DefaultKeyboardListener * GetInstance();
	

	void handleKeyEvent(KeyEvent * ke);


	virtual void handleKeyDown(KeyDownEvent * kde);


	virtual void handleKeyUp(KeyUpEvent * kue);


	/**
	 * Handles keys that have an ascii representation
	 */
    virtual void handleKey(KeyEvent* ke);

	virtual void handleKey_w();
	virtual void handleKey_s();
	virtual void handleKey_q();
	virtual void handleKey_e();
	virtual void handleKey_F();
	virtual void handleKeyAscii_27();

protected:
	
	DefaultKeyboardListener();


private:

	static DefaultKeyboardListener * _defaultKeyboardListener;

};

}

#endif			// DEFAULTKEYBOARDLISTENER_H
