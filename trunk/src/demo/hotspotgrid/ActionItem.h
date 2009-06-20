#ifndef ACTIONITEM_H
#define ACTIONITEM_H

#include "../../xor.h"
#include "Icon2D.h"

using namespace XOR;

/**
 * Model for the gui
 */
class ActionItem : public MouseListener
{

public:

    /**
     * Explicit constructor
     */
    ActionItem(Icon2D * icon, Action * action);

    /**
     * Returns the hull of the item's icon
     */
    Dimension2D * getIconHull();

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


private:
	Action * _action;
	bool _downInBounds;
	Icon2D * _icon;
};

#endif			// ACTIONITEM_H

