#ifndef PRINTMOUSEPOSITION_H
#define PRINTMOUSEPOSITION_H

#include <iostream>
#include "../../xor.h"

using namespace std;
using namespace XOR;

/**
 *
 */
class PrintMousePosition : public MouseListener
{

public:


    PrintMousePosition(Controller * ctrl);


    /**
     * Prints out the position of the mouse on click events
     */
    void handleMouseEvent(MouseEvent * me);


private:

    PrintMousePosition();
    Controller * _controller;
};


#endif			// PRINTMOUSEPOSITION_H

