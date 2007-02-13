#include "KeyboardStub.h"
namespace XOR {


KeyboardStub * KeyboardStub::_keyboardStub = NULL;
MulticastSocket * KeyboardStub::_socket = NULL;

KeyboardStub::~KeyboardStub()
{
    delete _socket;
}


/*
 * 
 */
KeyboardStub::KeyboardStub()
{
	_socket = MulticastSocketPool::GetInstance()->getMulticastSocket(
              MulticastSocketPool::KEYBOARD_SOCKET);
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

