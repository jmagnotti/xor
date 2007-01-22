#include "TimerStub.h"


namespace XOR {

TimerStub * TimerStub::_timerStub = 0;

TimerStub::TimerStub() : Timer(DEFAULT_TIMER_INTERVAL)
{}


TimerStub::~TimerStub()
{}


/*
 * Singleton Accessor
 */
TimerStub * TimerStub::GetInstance()
{
    if (_timerStub == NULL)
        _timerStub = new TimerStub();

    return _timerStub;
}


/*
 * notify listeners of the tick event
 */
void TimerStub::tickTock()
{
    //TODO multicast the timer event
    notifyListeners();
}

}

