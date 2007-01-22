#include "KeyboardStub.h"

namespace XOR {


KeyboardStub * KeyboardStub::_keyboardStub = 0;

    
KeyboardStub::KeyboardStub()
{}


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
    notifyListeners(ke);
    //TODO multicast receive
}

}

