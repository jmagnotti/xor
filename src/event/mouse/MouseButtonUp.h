#ifndef MOUSEBUTTONUP_H 
#define MOUSEBUTTONUP_H


#include "MouseClickEvent.h"
#include "Mouse.h"


namespace XOR {

/**
 * Represents the relase of of a mouse press. Most of the functionality is found in the 
 * abstract parent MouseClick
 */
class MouseButtonUp : public MouseClickEvent
{

public:


    MouseButtonUp(int x, int y, const int button);


    const int getType();

};

}

#endif          // MOUSEBUTTONUP_H

