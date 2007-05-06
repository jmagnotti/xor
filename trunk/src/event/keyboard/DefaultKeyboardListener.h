#ifndef DEFAULTKEYBOARDLISTENER_H
#define DEFAULTKEYBOARDLISTENER_H

#include <map>

#include "KeyboardListener.h"
#include "KeyEvent.h"
#include "../../interpolation/TimedInterpolation.h"
#include "../../core/Controller.h"
#include "../../core/World.h"


namespace XOR {

/** 
 * Represents the default key event behavior. Methods are purposely made virtual to allow
 * people to easily extend this classes behavior.
 */
class DefaultKeyboardListener : public KeyboardListener
{

public:


	DefaultKeyboardListener();

	/**
	 * Singleton Accessor  
	static DefaultKeyboardListener * GetInstance();
	 */
	

	void handleKeyEvent(KeyEvent * ke);


	virtual void handleKeyDown(KeyDownEvent * kde);


	virtual void handleKeyUp(KeyUpEvent * ke);


	/**
	 * Handles keys that have an ascii representation
	 */
    void handleKeyPressed(KeyEvent * ke);

protected:

	virtual void handleKey_w();
	virtual void handleKey_s();
	/*
	virtual void handleKey_q();
	virtual void handleKey_e();
	virtual void handleKey_a();
	virtual void handleKey_d();
	*/
	virtual void handleKey_F();

	
private:

	static DefaultKeyboardListener * _defaultKeyboardListener;

};

}

#endif			// DEFAULTKEYBOARDLISTENER_H

