#include "TimerSkeleton.h"


namespace XOR {

TimerSkeleton * TimerSkeleton::_timerSkeleton = NULL;
MulticastSocket * TimerSkeleton::_socket = NULL;

bool TimerSkeleton::_keepGoing = true;

TimerSkeleton::TimerSkeleton() : Timer(DEFAULT_TIMER_INTERVAL)
{}


/*
 * destructor
 */
TimerSkeleton::~TimerSkeleton()
{
	stop();
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

    while(_keepGoing) {
        _socket->receive();

        // we are pushing a TimerEvent onto the event queue. This has to be
        // done since this socket is listening in a sepearate thread.
        SDL_PushEvent(&_sdlTimerEvent);
    }
}


/**
 * only starts the timer if the socket has not been created
 */
void TimerSkeleton::start()
{
		_socket = MulticastSocketPool::GetInstance()->getMulticastSocket(
				  MulticastSocketPool::TIMER_SOCKET);

		_thread = SDL_CreateThread(& TimerSkeleton::Listen, this);
}


}

