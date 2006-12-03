#include "MouseListener.h"


namespace XOR {

/*
 * Default constructor, takes care of adding us to the mouse
 */
MouseListener::MouseListener()
{
    Mouse::GetInstance()->addListener(this);
}

}

