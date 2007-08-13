#ifndef DELAYEDACTION_H
#define DELAYEDACTION_H

#include "Action.h"
#include "timer/TimerListener.h"
#include "timer/IntervalTimer.h"

namespace XOR
{

/**
 * Invokes the specified action after at least the amount specified by the delay.
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0
 */
class DelayedAction : public Action, public TimerListener
{

public:

	DelayedAction(Action * action, int delay);

	virtual ~DelayedAction();

	void execute();

	void handleTick();

private:

	DelayedAction();

	Action * _action;

	int _delay;
};

}

#endif			// DELAYEDACTION_H
