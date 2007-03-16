#ifndef "LIGHTWEIGHTMENU_H
#define "LIGHTWEIGHTMENU_H

#include "../../xor.h"


using namespace XOR;

class LightweightMenu : public Object2D, public MouseListener
{

public:
    virtual void handleMouseEvent(MouseEvent me) = 0;

    virtual void renderObject() = 0;

};
#endif  //LIGHTWEIGHTMENU_H

