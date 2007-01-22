#ifndef MULTICASTBROADCASTER_H
#define MULTICASTBROADCASTER_H

#include "../event/keyboard/Keyboard.h"
#include "../event/keyboard/KeyboardListener.h"
#include "../event/keyboard/KeyEvent.h"
#include "../core/Controller.h"
#include "mcsend.h"


namespace XOR {

class MulticastBroadcaster : public KeyboardListener
{

public:

	MulticastBroadcaster();
	void handleKeyEvent(KeyEvent * ke);

private:

	MCSend * mcsend;
};

}

#endif			// MULTICASTBROADCASTER_H
