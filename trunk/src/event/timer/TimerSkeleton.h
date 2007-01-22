#ifndef TIMERSKELETON_H
#define TIMERSKELETON_H


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


    /**
     * Static singleton constructor with interval setting.
     */
    static TimerSkeleton * GetInstance();


    /**
     * This is the timer tick that does all the work. they are separated so 
     * people don't have to rely on the static method above.
     */
    void tickTock();


protected:
    
    // Default constructor
	TimerSkeleton();

    // Destructor
	virtual ~TimerSkeleton();

private:

    //MulticastReceiver * receiver;
    static TimerSkeleton *  _timerSkeleton;

};

}

#endif			// TIMERSKELETON_H

