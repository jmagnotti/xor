#include "DelayedAction.h"

namespace XOR
{

DelayedAction::DelayedAction(Action * action, int delay)
{
	_action = action;
	_delay  = delay;
}

DelayedAction::~DelayedAction()
{
}

/*
 * do the real work when the timer fires
 */
void DelayedAction::handleTick()
{
	_action->execute();
}


void DelayedAction::execute()
{
	IntervalTimer::GetInstance()->addCallbackListener(this, _delay);
}

}
