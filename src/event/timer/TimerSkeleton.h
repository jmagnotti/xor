#ifndef TIMERSKELETON_H
#define TIMERSKELETON_H


#include "../../../include/SDL_thread.h"
#include "../../multicast/MulticastSocket.h"
#include "../../multicast/MulticastSocketPool.h"

#include "Timer.h"


using namespace std;

namespace XOR {

/**
 * The timer will be called according to the value of TimerSkeleton.interval
 * The timer has a collection of TimerSkeletonListeners that it informs of tick
 * events.
 */
class TimerSkeleton : public Timer
{

public:

    // Destructor
	virtual ~TimerSkeleton();


    /**
     * Static singleton constructor with interval setting.
     */
    static TimerSkeleton * GetInstance();


    /**
     * This is the timer tick that does all the work. they are separated so 
     * people don't have to rely on the static method above.
     */
    void tickTock();


    /**
     * Waits for multicast broadcasts and pushes them onto the event queue
     */
    static int Listen(void * data);


private:
    
	TimerSkeleton();

    SDL_Thread * _thread;

    static bool _keepGoing;

    static MulticastSocket * _socket;

    static TimerSkeleton *  _timerSkeleton;

    void start();

};

}

#endif			// TIMERSKELETON_H

