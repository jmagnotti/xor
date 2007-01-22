#include "MouseSkeleton.h"


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
        updateFromEvent((MouseClickEvent*)me);

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

