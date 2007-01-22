#include "KeyboardSkeleton.h"

#include <iostream>
using namespace std;


namespace XOR {


KeyboardSkeleton * KeyboardSkeleton::_keyboardSkeleton = 0;


KeyboardSkeleton::KeyboardSkeleton()
{}

KeyboardSkeleton * KeyboardSkeleton::GetInstance()
{
    cout << "Getting an instance of the skeleton" << endl;

    if (_keyboardSkeleton == NULL)
        _keyboardSkeleton = new KeyboardSkeleton();

    return _keyboardSkeleton;
}


void KeyboardSkeleton::fireKeyEvent(KeyEvent * ke)
{
    cout << "Notifying the listeners" << endl;

    notifyListeners(ke);

    //TODO multicast receiving
}

}

