#include "KeyboardSkeleton.h"

#include <iostream>
using namespace std;


namespace XOR {


KeyboardSkeleton * KeyboardSkeleton::_keyboardSkeleton = NULL;
MulticastSocket  * KeyboardSkeleton::_socket = NULL;

bool KeyboardSkeleton::_keepGoing = true;

KeyboardSkeleton::~KeyboardSkeleton()
{
	_keepGoing = false;
	delete	_socket;
}

KeyboardSkeleton::KeyboardSkeleton()
{
	_socket = MulticastSocketPool::GetInstance()->getMulticastSocket(
			  MulticastSocketPool::KEYBOARD_SOCKET);

	_thread = SDL_CreateThread(& KeyboardSkeleton::Listen, NULL);
}

/*
 *
 */
KeyboardSkeleton * KeyboardSkeleton::GetInstance()
{
    if (_keyboardSkeleton == NULL)
        _keyboardSkeleton = new KeyboardSkeleton();

    return _keyboardSkeleton;
}


void KeyboardSkeleton::fireKeyEvent(KeyEvent * ke)
{
    notifyListeners(ke);
}


int KeyboardSkeleton::Listen(void * data)
{
	cout << "Keyboard Skeleton thread created." << endl;

	string msg; 
	KeyboardSkeleton * ks = KeyboardSkeleton::GetInstance();

	while(_keepGoing) {
		msg = _socket->receive();	
		ks->fireKeyEvent(KeyEventFactory::ConstructInstance(msg));
	}
}

}

