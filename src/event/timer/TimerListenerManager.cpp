#include "TimerListenerManager.h"

namespace XOR {

void TimerListenerManager::start(TimerListener * tl) 
{
	Controller::GetInstance()->getTimer()->addListener(tl);	
}

void TimerListenerManager::stop(TimerListener * tl) 
{
	Controller::GetInstance()->getTimer()->removeListener(tl);	
}

}

