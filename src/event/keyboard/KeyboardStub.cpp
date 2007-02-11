#include "KeyboardStub.h"
namespace XOR {


KeyboardStub * KeyboardStub::_keyboardStub = 0;

KeyboardStub::KeyboardStub()
{
	MulticastSocketPool * msp =	MulticastSocketPool::GetInstance();
	_socket = msp->getMulticastSocket(MulticastSocketPool::KEYBOARD_SOCKET);
}


KeyboardStub * KeyboardStub::GetInstance()
{
    if (_keyboardStub == NULL)
        _keyboardStub = new KeyboardStub();

    return _keyboardStub;
}


/*
 * fire events
 */
void KeyboardStub::fireKeyEvent(KeyEvent * ke)
{
	_socket->send(ke->toString());
    notifyListeners(ke);
}



}

