#include "EventRecorderFactory.h"

namespace XOR {

const int EventRecorderFactory::MOUSE_EVENT		= 0;
const int EventRecorderFactory::KEYBOARD_EVENT	= 1;
const int EventRecorderFactory::TIMER_EVENT		= 2;

const char * EventRecorderFactory::EVENTS_FILE	= "events.xer";

EventRecorderFactory::EventRecorderFactory(EventFactory * factory)
{
	_eventFactory	  = factory;
	_keyboardRecorder = new KeyboardRecorder();
	_mouseRecorder = new MouseRecorder();
	_timerRecorder = new TimerRecorder();
}

Keyboard * EventRecorderFactory::getKeyboard()
{
	Keyboard * k = _eventFactory->getKeyboard();
	k->addListener(_keyboardRecorder); 

	return k;
}

Timer * EventRecorderFactory::getTimer()
{
	Timer * t = _eventFactory->getTimer();
//	t->addListener(_timerRecorder);  // Generates lots of output

	return t;
}

Mouse * EventRecorderFactory::getMouse()
{
	Mouse * m = _eventFactory->getMouse();
	m->addListener(_mouseRecorder); 

	return m;
}

void MouseRecorder::handleMouseEvent(MouseEvent * me)
{

	if (Controller::GetInstance()->getTimer()->getElapsedFrames() > 0) {
		ofstream fout(EventRecorderFactory::EVENTS_FILE, ios::app);
		if (fout) {
			fout << EventRecorderFactory::MOUSE_EVENT << " " 
				 << Controller::GetInstance()->getTimer()->getElapsedFrames() 
				 << " " << me->toString() << endl;
			fout.close();
		}
	}
}

void KeyboardRecorder::handleKeyEvent(KeyEvent * ke)
{
	if (Controller::GetInstance()->getTimer()->getElapsedFrames() > 0) {
		ofstream fout(EventRecorderFactory::EVENTS_FILE, ios::app);
		if (fout) {
			fout << EventRecorderFactory::KEYBOARD_EVENT << " " 
				 << Controller::GetInstance()->getTimer()->getElapsedFrames() 
				 << " " << ke->toString() << endl;
			fout.close();
		}
	}
}

void TimerRecorder::handleTick() 
{
	if (Controller::GetInstance()->getTimer()->getElapsedFrames() > 0) {
		ofstream fout(EventRecorderFactory::EVENTS_FILE, ios::app);
		if (fout) {
			fout << EventRecorderFactory::TIMER_EVENT << " " 
				 << Controller::GetInstance()->getTimer()->getElapsedFrames()
				 << endl;
			fout.close();
		}
	}
}

}

