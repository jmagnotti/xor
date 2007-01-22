#ifndef TIMERLISTENER_H
#define TIMERLISTENER_H


namespace XOR {

/**
 * An interface to allow easy iteration over objects that need to be
 * informed of a timer.tickTock() event
 */
class TimerListener
{

public:

	virtual void handleTick()=0;

};

}

#endif		// TIMERLISTENER_H

