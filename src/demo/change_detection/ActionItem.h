#ifndef ACTIONITEM_H
#define ACTIONITEM_H

#include "../../xor.h"
#include "RectangularHull.h"

using namespace XOR;

/**
 * Model for the gui
 */
class ActionItem : public MouseListener, public Object2D
{

public:

    /**
     * Explicit constructor
     */
    ActionItem(Action * action);

	ActionItem(Action * action, Rectangle2D * pic);

    /**
     * Returns the hull of the item's icon
     */
    Dimension2D * getHull();

    /**
     * Takes care of mouse enter, mouse over, mouse leave, mouse down, mouse up,
     * and mouse click
     */
    void handleMouseEvent(MouseEvent * me);


    /**
     * Calls the execute() method
     */
    void execute();

    /**
     * Calls the render() method
     */
    void renderObject();

	/**
	 * Gets base vector
	 */
	Vector2D* getBaseVector();
	
	/**
	 * Gets the dimensions
	 */
	Dimension2D* getDimension();

	void setPaint(Paint *p);

private:
	Action * _action;
	bool _downInBounds;
	Rectangle2D * _picture;
	RectangularHull * _bounds;
};

#endif			// ACTIONITEM_H

