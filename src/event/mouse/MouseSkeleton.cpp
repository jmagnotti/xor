#include "MouseSkeleton.h"
#include <iostream>
using namespace std;

namespace XOR {

MouseSkeleton * MouseSkeleton::_mouseSkeleton = NULL;

/*
 * private constructor
 */
MouseSkeleton::MouseSkeleton()
{}


/*
 * Fires an event to listeners
 */
void MouseSkeleton::fireEvent(MouseEvent * me)
{
    if (me->getType() == MouseEvent::MOUSE_MOTION)
        updateFromEvent((MouseMotionEvent*)me);
    else 
        updateFromEvent((MouseClickEvent *)me);

    //cout << "Notifiying listeners of event type: " << me->getType() << endl;

    notifyListeners(me);

    //TODO multicast receiver
}


/*
 * Singleton Constructor
 */
MouseSkeleton * MouseSkeleton::GetInstance()
{
    if (_mouseSkeleton == NULL)
        _mouseSkeleton = new MouseSkeleton();

    return _mouseSkeleton;
}


}

