#ifndef ICON2D_H
#define ICON2D_H

#include "../../xor.h"
#include "RectangularHull.h"


using namespace XOR;

/**
 * A 2 Dimensional Icon class
 */
class Icon2D : public Object2D
{

public:

    /**
     * Explicit Constructor
     */
    Icon2D(Vector2D * origin, Dimension2D * size, char * iconPath);


    /**
     * Gets the icon's hull
     */
    Dimension2D * getIconHull();


    /**
     * Checks if x,y is in Icon bounds
     */
    bool inBounds(int xPos, int yPos);


    /**
     * Action when mouse button is pressed AND released inside of
     * icon bounds
     */
    void mouseClick();


    /**
     * Action when mouse enters the Icon bounds
     */
    void mouseEnter();


    /**
     * Action when mouse leaves the Icon bounds
     */
    void mouseLeave();


    /**
     * Action when mouse button is pressed
     */
    void mousePress();


    /**
     * Action when mouse button is released
     */
    void mouseRelease();


    /**
     * Renders the icon
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


private:
	RectangularHull * _bounds;
	Rectangle2D * _icon;
	Paint * _paint;
};


#endif			// ICON2D_H

