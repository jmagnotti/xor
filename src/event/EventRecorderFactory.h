#ifndef EVENTRECORDERFACTORY_H
#define EVENTRECORDERFACTORY_H

#include <iostream>
#include <fstream>

#include "../core/Controller.h"
#include "EventFactory.h"
#include "timer/Timer.h"
#include "timer/TimerListener.h"
#include "mouse/Mouse.h"
#include "mouse/MouseListener.h"
#include "keyboard/Keyboard.h"
#include "keyboard/KeyboardListener.h"

using namespace std;

namespace XOR {

class KeyboardRecorder;
class MouseRecorder;
class TimerRecorder;

/**
 * Dumps all events to EVENTS_FILE in an attempt to enable full-scale
 * replay of XOR Applications.
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0
 */
class EventRecorderFactory : public EventFactory
{

public:

    static const char * EVENTS_FILE;

    static const int ERF_KEYBOARD_EVENT;
    static const int ERF_MOUSE_EVENT;
    static const int ERF_TIMER_EVENT;


    EventRecorderFactory(EventFactory * factory);
    
    Keyboard * getKeyboard();

    Mouse * getMouse();
    
    Timer * getTimer();

private:


	EventFactory	 * _eventFactory;
	KeyboardRecorder * _keyboardRecorder;
	MouseRecorder	 * _mouseRecorder;
	TimerRecorder	 * _timerRecorder;
};

class MouseRecorder : public MouseListener
{ public: void handleMouseEvent(MouseEvent * me); };

class KeyboardRecorder : public KeyboardListener
{ public: void handleKeyEvent(KeyEvent * ke); };

class TimerRecorder : public TimerListener
{ public: void handleTick(); }; 

}

#endif			// EVENTRECORDERFACTORY_H

