#ifndef TIMERSTUB_H
#define TIMERSTUB_H


#include <string>
#include "Timer.h"

#include "../../multicast/MulticastSocket.h"
#include "../../multicast/MulticastSocketPool.h"


using namespace std;

namespace XOR {

/**
 * The timer will be called according to the value of TimerStub.interval
 * The timer has a collection of TimerStubListeners that it informs of tick
 * events.
 */
class TimerStub : public Timer
{

public:

    // Destructor
	virtual ~TimerStub();


    /**
     * Static singleton constructor with interval setting.
     */
    static TimerStub * GetInstance();


    /**
     * This is the timer tick that does all the work. they are separated so 
     * people don't have to rely on the static method above.
     */
    void tickTock();


private:

	TimerStub();

    static TimerStub * _timerStub;
    static string _eventString;

    static MulticastSocket  * _socket;

};

}

#endif			// TIMERSTUB_H

