#ifndef LIGHTWEIGHTMENU_H
#define LIGHTWEIGHTMENU_H

#include "../../xor.h"

using namespace XOR;

/**
 * A simple menu class
 */
class LightweightMenu : public Object2D, public MouseListener
{

public:
	/**
	 * Overridden by child classes to handle mouse events
	 *
	 * @param me - a mouse event
	 */
    virtual void handleMouseEvent(MouseEvent * me) = 0;

	/**
	 * Overridden by child classes to render themselves
	 */
    virtual void renderObject() = 0;

	/**
	 * Sets the menu visibility
	 *
	 * @param isVisible - the menu visiblity (true or false)
	 */
	void setVisible(bool isVisible);
	
	/**
	 * Gets the menu visibility
	 *
	 * @return - the menu visibility (true or false)
	 */
	bool isVisible();
	
private:
	bool _isVisible;

};
#endif  //LIGHTWEIGHTMENU_H

