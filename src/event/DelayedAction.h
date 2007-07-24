#ifndef DELAYEDACTION_H
#define DELAYEDACTION_H

#include "Action.h"
#include "timer/TimerListener.h"
#include "timer/IntervalTimer.h"

namespace XOR
{

class DelayedAction : public Action, public TimerListener
{

public:

	DelayedAction(Action * action, int delay);

	virtual ~DelayedAction();

	void execute();

	void handleTick();

private:

	Action();

	Action * _action;
	int _delay;
};

}

#endif			// DELAYEDACTION_H
