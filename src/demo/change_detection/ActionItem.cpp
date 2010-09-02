#include "ActionItem.h"

using namespace XOR;

/**
 * Explicit constructor
 */
ActionItem::ActionItem(Action * action, Rectangle2D * pic)
{
    _action = action;
    _downInBounds = false;

	_picture = pic;
	//let's add in a bit of a fudge factor, say 20 pixels on all sides
	Vector2D * newB = new Vector2D(_picture->getBaseVector()->getX()-20, _picture->getBaseVector()->getY()-20);
	Dimension2D * newD = new Dimension2D(_picture->getDimension()->getWidth()+40, _picture->getDimension()->getHeight() + 40);
    _bounds = new RectangularHull(newB, newD);
}

/**
 * Returns the hull of the item's icon
 */
Dimension2D * ActionItem::getHull()
{
    return NULL;
}

/**
 * Takes care of mouse enter, mouse over, mouse leave, mouse down, mouse up,
 * and mouse click
 */
void ActionItem::handleMouseEvent(MouseEvent * me)
{
    Mouse * mouse = Controller::GetInstance()->getMouse();


	//
	//This stuff goes kind of bonkers when working with the 
	//touchscreen, as you just get a serious of disconnected tapping
	//Having the action tied to MouseUp seems to alleviate the issues
	//
	
    if (me->getType() == MouseEvent::MOUSE_BUTTON_DOWN) {
        if(_bounds->inHull(mouse->getCurrentX(), mouse->getCurrentY()))
			execute();
    }
    else if (me->getType() == MouseEvent::MOUSE_BUTTON_UP) {
        if(_bounds->inHull(mouse->getCurrentX(), mouse->getCurrentY()))
			execute();
    }
}

/**
 * Calls the performAction() method
 */
void ActionItem::execute()
{
    _action->execute();
}

void ActionItem::setPaint(Paint *p) 
{
	_picture->setPaint(p);
}

void ActionItem::renderObject()
{
    _picture->renderObject();
}

Dimension2D * ActionItem::getDimension() {
	return _picture->getDimension();
}

Vector2D * ActionItem::getBaseVector() 
{
	return _picture->getBaseVector();
}
