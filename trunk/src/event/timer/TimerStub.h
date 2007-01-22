#ifndef TIMERSTUB_H
#define TIMERSTUB_H


#include "Timer.h"


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

    /**
     * Static singleton constructor with interval setting.
     */
    static TimerStub * GetInstance();


    /**
     * This is the timer tick that does all the work. they are separated so 
     * people don't have to rely on the static method above.
     */
    void tickTock();


protected:
    
    // Default constructor
	TimerStub();


    // Destructor
	virtual ~TimerStub();

private:

    //MulticastSender * sender;
    static TimerStub *  _timerStub;

};

}

#endif			// TIMERSTUB_H

