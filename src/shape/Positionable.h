#ifndef POSITIONABLE_H
#define POSITIONABLE_H


#include "Renderable.h"
#include "../transform/Orientate.h"


namespace XOR {

/**
 * Should be like an interface. Allows for generic treatment of all objects
 * that can be positioned as a unit.
 */
class Positionable : public Renderable
{

public:

	/**
	 * Default constructor
	 */
	Positionable();
	

    /**
     * Performs the rendering of the object
     */    
	virtual void render(void)=0;
	
	
	/**
	 * Returns true if the Positionable object has been positioned at all.
	 */
	bool isPositioned();
	
	
	/**
	 * Compile the Positionable to a display list.
	 */
	void compile();
	
	
	/**
	 * Decompile (don't use display list)
	 */
	void decompile();
	
	
	/**
	 * Returns true if the Positionable has been compiled yet
	 */
	bool isCompiled();
	
	
	/**
	 * Set the current orientation
	 */
	void setOrientate(Orientate * newOrientate);


    /**
     * Allows for copying or linking of two Positionables coordinates. This is 
     * mainly a convenience method, so one can do myCube.setPosition(otherCube)
     */
    void setPosition(Positionable * position, bool alias=false);


	/**
	 * Get the current orientation
	 */
	Orientate * getOrientate();


	/**
	 * Returns the class type. This should be used by sub-interfaces of renderable to 
	 * disambiguate themselves. See CollisionRenderable.h for an example.
	 */
	virtual char * getRenderableType();


protected:

	Orientate *	_orientation;

	bool   _compiled;
	bool   _positioned;

	GLuint _displayListID;

};

}

#endif		// POSITIONABLE_H

