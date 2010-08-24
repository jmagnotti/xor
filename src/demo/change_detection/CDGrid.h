#ifndef CDGRID_H
#define CDGRID_H

#include <vector>
#include "../../xor.h"

#include "ActionItem.h"
#include "RectangularHull.h"

using namespace XOR;
using namespace std;

/**
 * Hotspot grid class
 */
class CDGrid : public Object2D, public MouseListener
{

public:

    /**
     * Construct a grid with width gridSize at origin.
     */
    CDGrid();


    /**
     * Adds an already constructed action item
     */
    void addAction(ActionItem * item);


    /**
     * Handles the mouse click by determining which part of the grid was clicked
     * and calling performAction for the action associated with that grid location
     */
    void handleMouseEvent(MouseEvent * me);


	/*
	 * Allows the states to turn on/off mouse listening
	 */
	void setMouseListen(bool flag);
    
    
    /**
     * Returns the origin vector of the grid
     */
    Vector2D * getBaseVector();


    /**
     * Returns the dimensions of the grid
     */
    Dimension2D * getDimension();


    /**
     * Returns the next available grid location
     */
    Vector2D * getNextLocation();


    /**
     * Draws the grid
     */
    void renderObject();


	/**
	 * Sets the menu visibility
	 *
	 * @param isVisible - the menu visiblity (true or false)
	 */
	void setVisible(bool);

	
	/**
	 * Gets the menu visibility
	 *
	 * @return - the menu visibility (true or false)
	 */
	bool isVisible();


	void setVisibleLocations(vector<int>);

	void setImageFiles(vector<string>);

private:

	void rebuildImages();

	vector<ActionItem*> _actions;
	vector<int>	_locations;
	vector<string>	_imageFiles;

	RectangularHull * _bounds;
	Dimension2D * _size;
	Vector2D * _origin;

	bool _visible, _mouseHandle;
};


#endif			// CDGRID_H

