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
     * Specifies the offset required for centering stimuli in the "line-up" task
     * This function assumes 25 stimuli in the Initial display (24+fixation), 0-indexed.
     */
    static int GetLineUpStartPosition(int nStimuli);


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

	/**
	 * Pass-through to ALL Action Items, not just currently active ones (except
	 * fixation). Must do all because jitter at initial display, but need to
	 * nudge choice display items as well, and calling it then would result in
	 * double-nudging for all "no-change" items
	 */
	void jitter();

    /**
     * Connect the dots according to random node traversal
     */
	void rebuildConstellation();


private:

	void rebuildImages();

	vector<ActionItem*> _actions;
	vector<int>	_locations;
	vector<string>	_imageFiles;

    vector<Line2D*> _lines;

	RectangularHull * _bounds;
	Dimension2D * _size;
	Vector2D * _origin;

	bool _visible, _mouseHandle, _jitter, _constellation;
};


#endif			// CDGRID_H

