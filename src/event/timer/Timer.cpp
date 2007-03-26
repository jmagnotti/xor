#include "Timer.h"


namespace XOR {

SDL_Event   Timer::_sdlTimerEvent = {SDL_USEREVENT};

unsigned int Timer::_interval = DEFAULT_TIMER_INTERVAL;

/*
 * default cstr
 */
Timer::Timer()
{
    _sdlTimerEvent.type = SDL_USEREVENT;
    _sdlTimerEvent.user.code = TIMER_TICK_EVENT;
    _sdlTimerEvent.user.data1 = 0;
    _sdlTimerEvent.user.data2 = 0;
}

/*
 * Default Constructor
 */
Timer::Timer(unsigned int interval)
{
	_interval    = interval;
	_state       = DEFAULT_TIMER_STATE;
    _started     = false;

    // set to 0 to indicate that the timer has not started yet
    _timerHandle = 0;

    _sdlTimerEvent.type = SDL_USEREVENT;
    _sdlTimerEvent.user.code = TIMER_TICK_EVENT;
    _sdlTimerEvent.user.data1 = 0;
    _sdlTimerEvent.user.data2 = 0;
}


/*
 * Destructor
 */
Timer::~Timer()
{
    if (_timerHandle != NULL)
        SDL_RemoveTimer(_timerHandle);
}


/*
 * Adds a listener
 */
void Timer::addListener(TimerListener *tl)
{
    listeners.push_back(tl);
}


/*
 * Remove a listener from the pool
 */
void Timer::removeListener(TimerListener *tl)
{
    bool removed = false;

    list<TimerListener*>::iterator iter   = listeners.begin();
    list<TimerListener*>::iterator finish = listeners.end();

    while (!removed && iter != finish) {
        if (*iter == tl) {
            listeners.erase(iter);
            removed = true;
		}
		else {
			++iter;
		}
    }
}


/*
 * Sets the firing rate
 */
void Timer::SetInterval(unsigned int time)
{
	_interval  = time;
}


/*
 * Sets the timer state variable
 */
void Timer::setState(int state)
{
	_state = state;	
}


/*
 * starts the timer if it hasn't already been started
 */
void Timer::start()
{
    if (! _started) {
        _timerHandle = SDL_AddTimer(_interval, TickTock, (void *)_state);
        _started = true;
    }
}


/*
 * Deletes the timer 
 */
void Timer::stop()
{
	if (_started) {
		SDL_RemoveTimer(_timerHandle);
		_started = false;
	}
}


/*
 * Gets the timer interval. Note: This is not time elapsed
 */
unsigned int Timer::getInterval()
{
	return _interval;
}


/*
 * Returns the animation time
 */
int Timer::getElapsedTime()
{
    return SDL_GetTicks();
}


/*
 * Returns the the value of the state var that is passed to 
 * the timer function each tick
 */
int Timer::getState()
{
	return _state;
}


/*
 * The real timer function.
 * Called from the controller case statement. yes, this may be too
 * complicated...
 */
void Timer::notifyListeners()
{
    //this is a little more complicated since some listeners are going to be
    //removing themselves when they get a tick, so we need to be safe
    list<TimerListener*>::iterator iter   = listeners.begin();
	list<TimerListener*>::iterator next   = listeners.begin();
    list<TimerListener*>::iterator finish = listeners.end();

    while (iter != finish) {
		++next;
		(*iter)->handleTick();
        iter = next;
    }
}


/*
 * called when the sdl timer fires
 */
Uint32 Timer::TickTock(Uint32 interval, void * param)
{
    // set the next timer tick interval. note that we are using the class var as the source.
    interval = getInterval();

    // since this function may be called from another thread, we should push a
    // timer event onto the static event queue that is visible to all threads,
    // this ensures that timer ticks are always sequential.
    SDL_PushEvent(&_sdlTimerEvent);

    // this is the value that will be used for the next timer interval
    return interval;
}

}

