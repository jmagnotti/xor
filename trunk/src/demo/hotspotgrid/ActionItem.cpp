#include "ActionItem.h"

/**
 * Explicit constructor
 */
ActionItem::ActionItem(Icon2D * icon, GridAction * action)
{
    _icon = icon;
    _action = action;
    _downInBounds = false;
}

/**
 * Returns the hull of the item's icon
 */
Dimension2D * ActionItem::getIconHull()
{
    return _icon->getIconHull();
}

/**
 * Takes care of mouse enter, mouse over, mouse leave, mouse down, mouse up,
 * and mouse click
 */
void ActionItem::handleMouseEvent(MouseEvent * me)
{
    Mouse * mouse = Controller::GetInstance(NULL)->getMouse();

    if (me->getType() == MouseEvent::MOUSE_MOTION) {
        //mouse over
        if(_icon->inBounds(mouse->getCurrentX(), mouse->getCurrentY()))
            _icon->mouseEnter();
        else {
            _icon->mouseLeave();
            _downInBounds = false;
        }
    }
    // mouse button down event
    else if (me->getType() == MouseEvent::MOUSE_BUTTON_DOWN)
    {
        //mouse down
        if(mouse->isLeftButtonDown() && 
           _icon->inBounds(mouse->getCurrentX(), mouse->getCurrentY()))
        {
            _icon->mousePress();
            _downInBounds = true;
        }
    }

    // mouse up
    else {
        if(!(mouse->isLeftButtonDown())) {
            _icon->mouseRelease();

            if (_downInBounds)
                performAction();
        
            _downInBounds = false;
        }
    }

}

/**
 * Calls the performAction() method
 */
void ActionItem::performAction()
{
    _action->performAction();
}

/**
 * Calls the render() method
 */
void ActionItem::renderObject()
{
    _icon->renderObject();
}

