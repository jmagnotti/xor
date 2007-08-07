#ifndef TIMERLISTENERMANAGER_H
#define TIMERLISTENERMANAGER_H

#include "TimerListener.h"
#include "Timer.h"
#include "../../core/Controller.h"

namespace XOR {

class Controller;

/**
 * Utility methods for adding a class to the Timer. The idea is to reduce
 * dependencies by providing one class that knows about the Controller and
 * the Timer and TimerListeners.
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0
 */
class TimerListenerManager 
{

public:

	/**
	 * Removes the dependency on Controller.h and Timer.h on the timer
	 * listeners down the road.
	 *
	 * Adds the listener to the Timer's pool.
	 */
	static void start(TimerListener * tl);

	/**
	 * Removes the dependency on Controller.h and Timer.h on the timer
	 * listeners down the road.
	 *
	 * remove the listener from the Timer's pool
	 */
	static void stop(TimerListener * tl);

private:

	/**
	 * This will cause a compile-time error if you try to create one
	 */
	TimerListenerManager();

};

}

#endif			// TIMERLISTENERMANAGER_H

