#ifndef ROOM_H
#define ROOM_H


#include "../../xor.h"


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
	 * Default Constructor
	 */
	Room();


	/**
	 * Explicit Constructor
	 * Creates a room, using the given Volume for dimension
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
	void setPaint(Paint *);

	
	/**
	 * For now this is going to be used to put "paintings" on a wall
	 * You specify the Renderable and the wall to put it on.
	 */
	void setWallDecoration(Object3D *, int);


	Dimension3D * getDimension();

	Vector3D * getBaseVector();


protected:

	vector<Renderable*>	_decorations;
	Object3D * _renderable;

	Paint *				_paint;
		
};

#endif			// ROOM_H

