ude "PrintMousePosition.h"


/*
 * def cstr
 */
PrintMousePosition::PrintMousePosition(Controller * ctrl)
{
    _controller = ctrl;
    _controller->getMouse()->addListener(this);    
}


/*
 * print mouse.pos on me.type == down
 */
void PrintMousePosition::handleMouseEvent(MouseEvent * me)
{
    if (me->getType() == MouseEvent::MOUSE_BUTTON_DOWN) {
        cout << "Mouse pressed at: " << me->getXPosition() << ", " << me->getYPosition() << endl;

        Vector3D * mouseNearPosition = new Vector3D(me->getXPosition(), me->getYPosition(), 0.0);
        Vector3D * mouseFarPosition  = new Vector3D(me->getXPosition(), me->getYPosition(), 1.0);

        Vector3D * worldCoord = _controller->getCamera()->toWorldCoordinates(mouseNearPosition);

        cout << "near world coord: " << worldCoord->toString() << endl;

        delete worldCoord;

        worldCoord = _controller->getCamera()->toWorldCoordinates(mouseFarPosition);

        cout << "far world coord: " << worldCoord->toString() << endl;

        delete worldCoord;
        delete mouseNearPosition;
        delete mouseFarPosition;
    }
}

