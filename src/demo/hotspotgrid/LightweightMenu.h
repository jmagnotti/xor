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

	static const int VERTICAL_MENU	 = 0;
	static const int HORIZONTAL_MENU = 1;


	/**
	 * Returns a menu of the given type
	 */
	static LightweightMenu * CreateMenu(const int type);


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
	void setVisible(bool vis);

	
	/**
	 * Gets the menu visibility
	 *
	 * @return - the menu visibility (true or false)
	 */
	bool isVisible();


	/**
	 * Add an item to the menu
	 */
	void addItem(MenuItem * mi);

	
private:

	bool _visible;


};


/**
 * renders with a horizontal orientation
 */
class HorizontalMenu : public LightweightMenu
{

public:

	HorizontalMenu();

	/*
	 *
	 */
	void renderObject();
	
};


/**
 * renders with a horizontal orientation
 */
class VerticalMenu : public LightweightMenu
{

public:

	VerticalMenu();

	/*
	 *
	 */
	void renderObject();
	
};


#endif			// LIGHTWEIGHTMENU_H

