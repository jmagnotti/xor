#include "EventPlayerFactory.h"

namespace XOR {

EventPlayerFactory::EventPlayerFactory(EventFactory * factory)
{
	_eventFactory = factory;

	_keyboardPlayer = new KeyboardPlayer();
	_mousePlayer	= new MousePlayer();

	parse();
}

Timer * EventPlayerFactory::getTimer()
{
	Timer * t = _eventFactory->getTimer();

	t->addListener(_mousePlayer);
	t->addListener(_keyboardPlayer);

	return	t;
}

Keyboard * EventPlayerFactory::getKeyboard()
{
	//cout << "RETURN KEYBOARD" << endl;
	return _eventFactory->getKeyboard();
}

Mouse * EventPlayerFactory::getMouse()
{
	//cout << "RETURN MOUSE" << endl;
	return _eventFactory->getMouse();
} 

void EventPlayerFactory::parse()
{
	char *buffer;
	int type, frame;
	string message;

	//parse the file
	ifstream fin(EventRecorderFactory::EVENTS_FILE);		
	while(fin) {
		buffer = new char[50];
		memset(buffer, '\0', sizeof(buffer));	
		fin >> buffer;	// read in the event type
		type = atoi(buffer);

		memset(buffer, '\0', sizeof(buffer));	
		fin >> buffer;	// read in frame
		frame = atoi(buffer);

		if (EventRecorderFactory::MOUSE_EVENT == type) {
			message = "";
			//read in the type of mouse event
			memset(buffer, '\0', sizeof(buffer));
			fin >> buffer;	
			int me_type = atoi(buffer);

			message += buffer; // store mousEevent type
			message += " ";

			// read in the xpos, ypos, and val3 (button|xRel)
			for(int i=0; i<3; i++) { 
				memset(buffer, '\0', sizeof(buffer));
				fin >> buffer;	
				message += buffer;

				if (i<2) 
					message += " ";
			}

			// MOUSE_MOTION has an extra field (yRel)
			if (me_type == MouseEvent::MOUSE_MOTION) {
				memset(buffer, '\0', sizeof(buffer));
				fin >> buffer;
				message += " ";
				message += buffer;
			}
			//cout << "Adding mouseevent: " << message << " for frame: " << frame << endl;
			_mousePlayer->addEvent(message, frame);
		}
		else if (EventRecorderFactory::KEYBOARD_EVENT) {
			message = "";
			// read in Type, Key, and MODs
			for(int i=0; i<3; i++) {
				memset(buffer, '\0', sizeof(buffer));	
				fin >> buffer;
				message += buffer;
				if (i<2) message += " ";
			}
			_keyboardPlayer->addEvent(message, frame);
		}

		delete buffer;
	}
	fin.close();

	//_keyboardPlayer->debug();
}

void EventPlayer::addEvent(string event, int frame)
{
	if (frame > 0) {
		vector<string> * _temp = _events[frame];	
		if (_temp == NULL)
			_temp = new vector<string>();

		_temp->push_back(event);
		_events[frame] = _temp;
	}
}

void EventPlayer::debug()
{
	cout << "BEGIN EventPlayer::debug()" << endl;
	map<int, vector<string>*>::iterator iter  = _events.begin();
	map<int, vector<string>*>::iterator finish = _events.end();

	while (iter != finish) {
		for(int i=0; i<iter->second->size(); i++)
			cout << (*(iter->second))[i] << endl;
		++iter;
	}
	cout << "END EventPlayer::debug()" << endl;
	
}

EventPlayer::EventPlayer()
{
	_frameCount = 0;
}

EventPlayer::~EventPlayer()
{
	map<int, vector<string>*>::iterator iter  = _events.begin();
	map<int, vector<string>*>::iterator next  = _events.begin();
	map<int, vector<string>*>::iterator finish = _events.end();

	while (iter != finish) {
		++next;
		delete (iter->second);
		_events.erase(iter);
		iter = next;
	}
}

void EventPlayer::handleTick()
{
	Timer * t = Controller::GetInstance()->getTimer();

	map<int, vector<string>*>::iterator iter  = _events.begin();
	map<int, vector<string>*>::iterator finish = _events.end();

	bool keepGoing = true;
	while (iter != finish && keepGoing) {
		if (iter->first > _frameCount) { // skip passed the frames we have already run
			   if(iter->first <= t->getElapsedFrames()) {
				for(int i=0; i<iter->second->size(); i++) {
					fireEvent((*(iter->second))[i]);
				}
			}
			else {
				//cout << "Bailed on frame: " << t->getElapsedFrames() << " with next event at frame: " << iter->first << endl;
				keepGoing = false;
			}
		}
		++iter;
	}
	_frameCount = t->getElapsedFrames();
}

void MousePlayer::fireEvent(string event)
{
	Mouse::FireSDLEvent(MouseEventFactory::ConstructSDLEvent(event));
}

void KeyboardPlayer::fireEvent(string event)
{
	//cout << "KP::Building : " << event << endl;
	Keyboard::FireSDLEvent(KeyEventFactory::ConstructSDLEvent(event));
	//cout << "Succesful K fire" << endl;
}

}

