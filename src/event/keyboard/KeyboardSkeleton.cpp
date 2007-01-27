#include "KeyboardSkeleton.h"

#include <iostream>
using namespace std;


namespace XOR {


KeyboardSkeleton * KeyboardSkeleton::_keyboardSkeleton = 0;


KeyboardSkeleton::KeyboardSkeleton()
{}

KeyboardSkeleton * KeyboardSkeleton::GetInstance()
{
    if (_keyboardSkeleton == NULL)
        _keyboardSkeleton = new KeyboardSkeleton();

    return _keyboardSkeleton;
}


void KeyboardSkeleton::fireKeyEvent(KeyEvent * ke)
{
    cout << "firing key event: " << ke->getKey() << endl;

    notifyListeners(ke);

    //TODO multicast receiving
}

}

