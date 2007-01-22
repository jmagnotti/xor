#include "ReshapeSkeleton.h"


namespace XOR {

ReshapeSkeleton * ReshapeSkeleton::_reshapeSkeleton = 0;

/*
 * default constructor
 */
ReshapeSkeleton::ReshapeSkeleton()
{}


/*
 * send the event to the listeners
 */
void ReshapeSkeleton::fireEvent(ReshapeEvent * event)
{
    notifyListeners(event);
}


/*
 * singleton accessor
 */
ReshapeSkeleton * ReshapeSkeleton::GetInstance()
{
    if (_reshapeSkeleton == NULL)
        _reshapeSkeleton = new ReshapeSkeleton();

    return _reshapeSkeleton;
}

}

