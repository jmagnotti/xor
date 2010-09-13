#include "ActionItem.h"
#include <cstdlib>

using namespace XOR;

/**
 * Explicit constructor
 */
ActionItem::ActionItem(Action * action, Rectangle2D * pic)
{
	Helper::SeedGenerator();

    _action = action;
    _downInBounds = false;
	_jitterThreshold = 20;
	_jitterVector = new Vector2D(0,0);

	_picture = pic;

	updateBoundingBox();
}

void ActionItem::updateBoundingBox()
{
	//let's add in a bit of a fudge factor, say 10 pixels on all sides
	int pad = 10;

	Vector2D * newB = new Vector2D(_picture->getBaseVector()->getX()-pad, _picture->getBaseVector()->getY()-pad);

	Dimension2D * newD = new Dimension2D(_picture->getDimension()->getWidth()+2*pad, _picture->getDimension()->getHeight() + 2*pad);

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
	
    if (me->getType() == MouseEvent::MOUSE_BUTTON_UP) {
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

void ActionItem::jitter()
{
	Vector2D * _unJitter = _jitterVector->invert();

	_picture->nudge(_unJitter);

	delete _jitterVector;
	delete _unJitter;

	//range [-_jitterThreshold, _jitterThreshold]
	int offX = (rand() % (2*_jitterThreshold)) - _jitterThreshold;
	int offY = (rand() % (2*_jitterThreshold)) - _jitterThreshold;

	_jitterVector = new Vector2D(offX, offY);

	_picture->nudge(_jitterVector);

	updateBoundingBox();

	cout << _jitterVector->toString() << endl;
}

void ActionItem::setJitterThreshold(int threshold)
{
	_jitterThreshold = threshold;
}

Dimension2D * ActionItem::getDimension() {
	return _picture->getDimension();
}

Vector2D * ActionItem::getBaseVector() 
{
	return _picture->getBaseVector();
}
