#ifndef CONTINUOUSACTION_H
#define CONTINUOUSACTION_H

#include "Action.h"
#include "timer/TimerListener.h"
#include "timer/TimerListenerManager.h"

namespace XOR
{

/**
 * An action that, once exectued, continues to exectue on every timer tick
 * until stopExecuting() is called.
 * 
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0
 */
class ContinuousAction : public Action, public TimerListener
{

public:

	ContinuousAction(Action * action);

	virtual ~ContinuousAction();

	void execute();

	void stopExecuting();

	void handleTick();

private:

	ContinuousAction();
	Action * _action;

};

}

#endif			// CONTINUOUSACTION_H
