#include "TimerSkeleton.h"


namespace XOR {

TimerSkeleton * TimerSkeleton::_timerSkeleton = NULL;
MulticastSocket * TimerSkeleton::_socket = NULL;

bool TimerSkeleton::_keepGoing = true;

TimerSkeleton::TimerSkeleton()
{
    cout << "Creating Skeleton" << endl;
    _socket = MulticastSocketPool::GetInstance()->getMulticastSocket(
              MulticastSocketPool::TIMER_SOCKET);

    _thread = SDL_CreateThread(& TimerSkeleton::Listen, NULL);
}


/*
 * destructor
 */
TimerSkeleton::~TimerSkeleton()
{
    _keepGoing = false;
    delete _socket;
}


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


/*
 * Handles multicast timer ticks 
 */
int TimerSkeleton::Listen(void * data)
{
    string msg;

    TimerSkeleton * ts = TimerSkeleton::GetInstance();

    while(_keepGoing) {
        msg = _socket->receive();
        ts->tickTock();
    }

}

void TimerSkeleton::start()
{}


}

