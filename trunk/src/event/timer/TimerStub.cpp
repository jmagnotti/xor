#include "TimerStub.h"


namespace XOR {

TimerStub * TimerStub::_timerStub = NULL;
MulticastSocket * TimerStub::_socket = NULL;
string TimerStub::_eventString = "Tick";

TimerStub::TimerStub() : Timer(DEFAULT_TIMER_INTERVAL)
{
    _socket = MulticastSocketPool::GetInstance()->getMulticastSocket(
    MulticastSocketPool::TIMER_SOCKET);
}


TimerStub::~TimerStub()
{
    delete _socket;
}


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
    _socket->send(_eventString);
    notifyListeners();
}

}

