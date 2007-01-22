#include "MouseStub.h"


namespace XOR {

MouseStub * MouseStub::_mouseStub = 0;

/*
 * private constructor
 */
MouseStub::MouseStub()
{}


/*
 * Singleton accessor
 */
MouseStub * MouseStub::GetInstance()
{
    if (_mouseStub == NULL)
        _mouseStub = new MouseStub();

    return _mouseStub;
}


/*
 * fire events to listeners
 */
void MouseStub::fireEvent(MouseEvent * me)
{
    notifyListeners(me);
}

}

