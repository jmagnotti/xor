#ifndef ACTIONITEM_H
#define ACTIONITEM_H

#include "../../xor.h"
#include "RectangularHull.h"
#include "Helper.h"

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
     * Get center vector
     */
    Vector2D * getCenterVector();
	
	/**
	 * Gets the dimensions
	 */
	Dimension2D* getDimension();

	void setPaint(Paint *p);

	/*
	 * Maximal, per-axis (X,Y) threshold
	 */
	void setJitterThreshold(int threshold);

	/**
	 * Peturb image location according to <X,Y> iid U[-threshold, threshold]
	 * Jitters based on ORIGINAL item location, so setting Jitter threshold
	 * sets a bounding box for the movement space of the point of origin.
	 * 
	 * The bounding box for the ActionItem is updated after each call to jitter();
	 */
	void jitter();

private:

	void updateBoundingBox();

	Action * _action;
	bool _downInBounds;
	Rectangle2D * _picture;
	
	RectangularHull * _bounds;
	int _jitterThreshold;
	Vector2D * _jitterVector;
};

#endif			// ACTIONITEM_H

