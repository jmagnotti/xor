#ifndef TIMERLISTENER_H
#define TIMERLISTENER_H


namespace XOR
{

/**
 * An interface to allow easy iteration over objects that need to be
 * informed of a timer.tickTock() event
 * 
 * @author John Magnotti
 * @author Michael Lam
 * 
 * @version 1.0
 */
class TimerListener
{

public:

	/**
	 * Code in this method will be executed according to timer ticks,
	 * assuming the object has been added to the Timer's listener pool already.
	 *
	 * @see TimerListenerManager
	 */
	virtual void handleTick()=0;

};

}

#endif		// TIMERLISTENER_H

