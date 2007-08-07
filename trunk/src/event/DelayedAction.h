#ifndef DELAYEDACTION_H
#define DELAYEDACTION_H

#include "Action.h"
#include "timer/TimerListener.h"
#include "timer/IntervalTimer.h"

namespace XOR
{

/**
 * Invokes the specified action after the at least the amount specified by the delay.
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
