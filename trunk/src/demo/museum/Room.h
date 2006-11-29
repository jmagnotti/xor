#ifndef ROOM_H
#define ROOM_H


#include "Paint.h"
#include "Renderable.h"
#include "RectangularPrism.h"
#include "RectangularVolume.h"


/**
 * Represents a volume of space that can be painted and have PositionableRenderables rendered
 * onto an arbitrary surface
 * Ex. You can render a picture on a wall.
 */
class Room : public Renderable
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
	Room(RectangularVolume *);


	/**
	 * Explicit Constructor
	 * Creates a room, using the given Prism for dimension & paint
	 */
	Room(RectangularPrism *);


	/**
	 * Renders the room
	 */
	void render(void);


	/**
	 * Sets the volume for the room
	 * Note: This causes a lot of recalculation
	 */
	void setVolume(RectangularVolume *);


	/**
	 * Sets the prism for the room
	 * Note: This causes a lot of recalculation
	 */
	void setPrism(RectangularPrism *);


	/**
	 * Sets the paint for the room
	 */
	void setPaint(Paint *);

	
	/**
	 * For now this is going to be used to put "paintings" on a wall
	 * You specify the Renderable and the wall to put it on.
	 */
	void setWallDecoration(Renderable *, int);


protected:

	vector<Renderable*>	_decorations;

	Paint *				_paint;
	RectangularPrism	_renderable;
	
};


#endif			// ROOM_H
