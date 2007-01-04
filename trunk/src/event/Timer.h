#ifndef TIMER_H
#define TIMER_H

#include <vector>
#include <list>

#include "../../include/SDL.h"
#include "TimerListener.h"


#include <iostream>

using namespace std;

namespace XOR {

/**
 * The timer will be called according to the value of Timer.interval
 * The timer has a collection of TimerListeners that it informs of tick events.
 */
class Timer
{

public:

    /**
     * A define to be used for the SDL_Event
     */
    static const int            TIMER_TICK_EVENT        = 1000;


	/**
	 * Used in the constructor to suggest a timer interval to the controller
	 */
	static const unsigned int	DEFAULT_TIMER_INTERVAL	= 20;


	/**
	 * State is just an int that is passed along to the timerListeners
	 */
	static const int			DEFAULT_TIMER_STATE		= 1;


    /**
     * Static singleton constructor with interval setting.
     */
    static Timer * GetInstance(unsigned int milliseconds=DEFAULT_TIMER_INTERVAL);


    /*
     * Adds a listener
     */
    void addListener(TimerListener * tl);

    
    /**
	 * Gets the timer interval. Note: This is not time elapsed
	 */
	unsigned int getInterval();


	/*
	 *  Returns the animation time
	 */
	int getElapsedTime();

	
	/**
	 * Returns the the value of the state var that is passed to 
	 * the timer function each tick
	 */
	int getState();


	/** 
	 * Sets the timer interval in milliseconds
	 */
	void setInterval(unsigned int time);


	/**
	 * Sets the state variable for the timer
	 */
	void setState(int state);


    /**
     * Removes the listener from the vector.
     */
    void removeListener(TimerListener * tl);


    /*
     * allocates and starts  timer
     */
    void start();
    

    /*
     * stops and deallocates the timer
     */
    void stop();


    /**
     * SDL Timer Handler. This should only be called by SDL.
     */
    static Uint32 TickTock(Uint32 interval, void * param); 


    /**
     * This is the timer tick that does all the work. they are separated so 
     * people don't abuse the static method above.
     */
    void tickTock();


protected:
    
    // Default constructor
	Timer(unsigned int interval=DEFAULT_TIMER_INTERVAL);

    // Destructor
	~Timer();

    //vector<TimerListener*> listeners;
	list<TimerListener*> listeners;

    bool            _started;
	int             _state;
	unsigned int    _interval;
    
    static SDL_Event    _sdlTimerEvent;
    SDL_TimerID         _timerHandle;
    

private:

    static Timer *  _timer;

};

}

#endif			//TIMER_H

