#ifndef TIMER_H
#define TIMER_H


#include <list>
#include <math.h>

#include "../../../include/SDL.h"
#include "TimerListener.h"


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
	 * Most timer implementations pass around a state variable, this state
	 * represents the default state of operation. As of XOR_2.0.0 this is
	 * the only state implemented.
	 */
	static const int			DEFAULT_TIMER_STATE		= 1;

    /*
     * Destructor
     */
	virtual ~Timer();


    /*
     * Adds a listener
     */
    void addListener(TimerListener * tl);

    
    /**
     * Gets the timer interval. Note: This is not time elapsed, but rather the
     * firing interval. This method is static so we can interact with the SDL
     * TickTock method which must be static
	 */
	static unsigned int getInterval(); 


	/*
	 *  Returns the animation time
	 */
	int getElapsedTime();
	int getElapsedFrames();

	
	/**
	 * Returns the the value of the state var that is passed to 
	 * the timer function each tick
	 */
	int getState();


	/** 
	 * Sets the timer interval in milliseconds
	 */
	static void SetInterval(unsigned int time);


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
    virtual void start();
    

    /*
     * stops and deallocates the timer
     */
    void stop();


    /**
     * SDL Timer Handler. This should only be called by SDL. Calling this
     * function will not necessarily cause the timer to fire. 
     */
    static Uint32 TickTock(Uint32 interval, void * param); 


    /**
     * This is the timer tick that does all the work. they are separated so 
     * people don't have to rely on the static method above.
     */
    virtual void tickTock()=0;

    /**
     *
     */
    static int millisecondsToFrames(int milliseconds);

    /**
     *
     */
    static int framesToMilliseconds(int frames);


protected:

    /**
     * calls the handleTick method on all the listeners.
     */
    void notifyListeners();


    /*
     * Construct with a callback interval.
     */
	Timer(unsigned int interval);


    // Timers can only be created with an interval.
	Timer();

    static SDL_Event    _sdlTimerEvent;

private:

	list<TimerListener*> listeners;

    bool					_started;
	int						_state;
    unsigned int			_frames;
	static unsigned int		_interval;
    
    SDL_TimerID         _timerHandle;
    
};

}

#endif			//TIMER_H

