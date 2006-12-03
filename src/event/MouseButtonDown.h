#ifndef MOUSEBUTTONDOWN_H 
#define MOUSEBUTTONDOWN_H


#include "MouseClickEvent.h"
#include "Mouse.h"


namespace XOR {

/**
 * Represents the press of of a mouse button. Most of the functionality is found in the 
 * abstract parent MouseClick
 */
class MouseButtonDown : public MouseClickEvent
{

    public:

        MouseButtonDown(const int * button, Uint16 * x, Uint16 * y);

        const int * getType();

    protected:

        MouseButtonDown();


};

}

#endif          // MOUSEBUTTONDOWN_H

