#include "ContinuousAction.h"

namespace XOR { 

ContinuousAction::ContinuousAction(Action * action)
{
	_action = action;
}

ContinuousAction::~ContinuousAction()
{
}

void ContinuousAction::execute()
{
	TimerListenerManager::start(this);
}

void ContinuousAction::handleTick()
{
	_action->execute();
}

void ContinuousAction::stopExecuting()
{
	TimerListenerManager::stop(this);
}

}

