#include "IntervalTimer.h"

namespace XOR {


IntervalTimer * IntervalTimer::_intervalTimer = NULL;


/*
 * default constructor
 */
IntervalTimer::IntervalTimer()
{ }


/*
 * singleton accessor
 */
IntervalTimer * IntervalTimer::GetInstance()
{
	if (_intervalTimer == NULL) {
		_intervalTimer = new IntervalTimer();
		Controller::GetInstance(NULL)->getTimer()->addListener(_intervalTimer);
	}
	return _intervalTimer;
}


/*
 * add a recurring listener
 */
void IntervalTimer::addRegularListener(TimerListener * tl, int milliseconds)
{
	addListener(tl, milliseconds, true);
}


/*
 * add a one-time listener
 */
void IntervalTimer::addCallbackListener(TimerListener * tl, int milliseconds)
{
	addListener(tl, milliseconds, false);
}


/*
 * add a one-time or recurring listener
 */
void IntervalTimer::addListener(TimerListener * tl, int milliseconds, bool recurring)
{
	ListenerProperties * newListenerProperties = new ListenerProperties();
	newListenerProperties->_listener = tl;
	newListenerProperties->_interval = milliseconds;
	newListenerProperties->_recurring = recurring;
	newListenerProperties->_done = false;
	resetTicksRemaining(newListenerProperties);
	listeners.push_back(newListenerProperties);
}


/*
 * cancel a listener
 */
void IntervalTimer::removeListener(TimerListener * tl)
{
    bool removed = false;

    list<ListenerProperties*>::iterator iter   = listeners.begin();
    list<ListenerProperties*>::iterator finish = listeners.end();

    while (!removed && iter != finish) {
        if ((*iter)->_listener == tl) {
            listeners.erase(iter);
            removed = true;
		}
		else {
			++iter;
		}
    }
}

/*
 * notify listeners
 */
void IntervalTimer::handleTick()
{
    list<ListenerProperties*>::iterator iter   = listeners.begin();
    list<ListenerProperties*>::iterator finish = listeners.end();

    while (iter != finish) {
		if ((*iter)->_done == false) {
			if ((*iter)->_ticksRemaining <= 0) {
				(*iter)->_listener->handleTick();
				if ((*iter)->_recurring == false)
					(*iter)->_done = true;
				else
					resetTicksRemaining(*iter);
			}
			else {
				(*iter)->_ticksRemaining --;
			}
		}
		++iter;
    }

	purgeDone();
}


/*
 * reset the counter for an expired timer
 */
void IntervalTimer::resetTicksRemaining(ListenerProperties * lp)
{
	lp->_ticksRemaining = (int)(lp->_interval /
			(double)Controller::GetInstance(NULL)->getTimer()->getInterval());
}


/*
 * get rid of non-active listeners
 */
void IntervalTimer::purgeDone()
{
    bool removed = false;
	bool clear = false;

	while (clear == false) {
		removed = false;

		list<ListenerProperties*>::iterator iter   = listeners.begin();
		list<ListenerProperties*>::iterator finish = listeners.end();

		while (!removed && iter != finish) {
			if ((*iter)->_done == true) {
				listeners.erase(iter);
				removed = true;
			}
			else {
				++iter;
			}
		}
		if (!removed)
			clear = true;
	}
}

}

