#ifndef INTERVALTIMER_H
#define INTERVALTIMER_H

#include <list>

#include "../../core/Controller.h"
#include "TimerListener.h"

using namespace std;

namespace XOR {

/**
 * Enhances the standard timer by doing all the messy interval
 * and remaining-ticks calculation. All the application developer needs
 * to know is the desired millisecond interval and whether the event is
 * one-time or recurring.
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0
 */
class IntervalTimer : public TimerListener
{

public:

	/**
	 * Singleton accessor
	 */
	static IntervalTimer * GetInstance();

	/**
	 * Add a recurring listener
	 */
	void addRegularListener(TimerListener * tl, int milliseconds);

	/**
	 * Add a one-time listener
	 */
	void addCallbackListener(TimerListener * tl, int milliseconds);

	/**
	 * Add a one-time or recurring listener
	 */
	void addListener(TimerListener * tl, int milliseconds, bool recurring);

	/**
	 * Remove a listener
	 */
	void removeListener(TimerListener * tl);

	/**
	 * Performs the remaining-tick calculations and calls handleTock()
	 * if the interval is up.
	 */
	void handleTick(); 

private:

	/**
	 * Association structure for storing TimerListener information
	 */
	struct ListenerProperties
	{
		TimerListener *	_listener;
		int				_interval;
		int				_ticksRemaining;
		bool			_recurring;
		bool			_done;
	};

	/**
	 * Recalculate ticks remaining on a given listener
	 */
	void resetTicksRemaining(ListenerProperties * lp);

	/**
	 * Clear all "done" timers
	 */
	void purgeDone();

	static IntervalTimer * _intervalTimer;

	list<ListenerProperties*> listeners;

	/**
	 * Default constructor
	 */
	IntervalTimer();

};

}

#endif		// INTERVALTIMER_H

