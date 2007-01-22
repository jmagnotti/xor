#include "TimerSkeleton.h"


namespace XOR {

TimerSkeleton * TimerSkeleton::_timerSkeleton = 0;

TimerSkeleton::TimerSkeleton() : Timer(DEFAULT_TIMER_INTERVAL)
{}

TimerSkeleton::~TimerSkeleton()
{}

/*
 * Singleton Accessor
 */
TimerSkeleton * TimerSkeleton::GetInstance()
{
    if (_timerSkeleton == NULL)
        _timerSkeleton = new TimerSkeleton();

    return _timerSkeleton;
}


/*
 * notify listeners of the tick event
 */
void TimerSkeleton::tickTock()
{
    notifyListeners();
}

}

