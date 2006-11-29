#ifndef DEFAULTKEYBOARDLISTENER_H
#define DEFAULTKEYBOARDLISTENER_H

#include <map>

#include "KeyboardListener.h"
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
	

	/**
	 * Handles non-ascii keys
	 */
	virtual void handleKey(SpecialKeyEvent* ske);


	/**
	 * Handles keys that have an ascii representation
	 */
	virtual void handleKey(RegularKeyEvent* rke);

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

