#ifndef EVENTPLAYERFACTORY_H
#define EVENTPLAYERFACTORY_H

#include <string>
#include <vector>
#include <map>

#include "EventFactory.h"
#include "EventRecorderFactory.h"
#include "../core/Controller.h"
#include "timer/Timer.h"
#include "timer/TimerListener.h"

using namespace std;

namespace XOR {

class MousePlayer;
class KeyboardPlayer;

/**
 * Sets up playback tools that will resend events according to the values
 * specified in EventRecorderFactory::EVENTS_FILE
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0
 */
class EventPlayerFactory : public EventFactory
{

public:
    
    EventPlayerFactory(EventFactory * factory);
    
    Keyboard * getKeyboard();
    
    Mouse * getMouse();
    
    Timer * getTimer();

private:

	void parse();

	EventFactory * _eventFactory;

	KeyboardPlayer	* _keyboardPlayer;
	MousePlayer		* _mousePlayer;
};

class EventPlayer : public TimerListener
{
public:
	EventPlayer();
	virtual ~EventPlayer();
	void addEvent(string event, int frame); 
	void handleTick();
	void debug();
protected:
	virtual void fireEvent(string event)=0;
private:
	map <int, vector<string>*> _events;
	int _frameCount;
};

class MousePlayer : public EventPlayer
{ public: void fireEvent(string event); };

class KeyboardPlayer : public EventPlayer 
{ public: void fireEvent(string event); };

}

#endif			// EVENTPLAYERFACTORY_H

