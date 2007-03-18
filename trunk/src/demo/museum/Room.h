#ifndef ROOM_H
#define ROOM_H


#include <vector>
#include "../../xor.h"

#include "DoorExtracter.h"


using namespace std;
using namespace XOR;

/**
 * Represents a volume of space that can be painted and have PositionableRenderables rendered
 * onto an arbitrary surface
 * Ex. You can render a picture on a wall.
 */
class Room : public Object3D
{

public:


	/**
	 * Explicit Constructor
	 * Creates a room, using the given Volume for dimension. 
	 */
	Room(RectangularVolume * volume);


	/**
	 * Explicit Constructor
	 * Creates a room, using the given Prism for dimension & paint
	 */
	Room(RectangularPrism * prism);


	/**
	 * Renders the room
	 */
	void renderObject(void);


	/**
	 * Sets the paint for the room
	 */
	void setPaint(Paint * paint);


    /**
     * Make an entrance to this room on a given wall
     *
     * @param face  The wall to create a door on. Valid constants are defined
     *              in RectangularPrism.h
     */
    void extractDoor(const int face);


    /*
     * returns a clone of the current paint object
     */
	Paint * getPaint();

	
	/**
	 * For now this is going to be used to put "paintings" on a wall
	 * You specify the Renderable and the wall to put it on.
	 */
	void setWallDecoration(Object3D *, int);


	Dimension3D * getDimension();

	Vector3D * getBaseVector();


private:

	/**
	 * Private Constructor
	 */
	Room();

	vector<Object3D*>	 _decorations;
	Object3DCollection * _entranceWay;

	Paint *	_paint;
	RectangularPrism * _renderable;

		
};

#endif			// ROOM_H

