#include "Positionable.h"

namespace XOR {

/*
 * default constructor
 */
Positionable::Positionable()
{
	_orientation = new Orientate();
	_compiled = false;
	_positioned = false;
}


/*
 * Returns true if the Positionable object has been positioned at all.
 */
bool Positionable::isPositioned()
{
	return _positioned;
}


/*
 * Compile the Positionable to a display list.
 */
void Positionable::compile()
{
	if (!_compiled)
	{
		_displayListID = glGenLists(1);
	
		glNewList(_displayListID, GL_COMPILE);
			render();
		glEndList();
	
		_compiled = true;
		_positioned = false;
		
		delete _orientation;
		_orientation = new Orientate();
	}
}


/*
 * Cancel display list.
 */
void Positionable::decompile()
{
	_compiled = false;
}


/*
 * Returns true if the Positionable has been compiled yet
 */
bool Positionable::isCompiled()
{
	return _compiled;
}


/*
 * Set the current orientation
 */
void Positionable::setOrientate(Orientate * newOrientate)
{
    delete _orientation;
	_positioned = true;
	_orientation = newOrientate;
}


/*
 * Synch the objects position with that of the others position. The alias 
 * variable controls whether the positions are linked or copied.
 */
void Positionable::setPosition(Positionable * position, bool alias)
{
    if (alias)
        setOrientate(position->getOrientate());
    else
        _orientation->clone(position->getOrientate());
}


/*
 * Get the current orientation
 */
Orientate * Positionable::getOrientate()
{
	_positioned = true;
	return _orientation;
}


/**
 * Returns the class type. This should be used by sub-interfaces of renderable to 
 * disambiguate themselves. See CollisionRenderable.h for an example.
 */
char * Positionable::getRenderableType()
{
	return "POSITIONABLE";
}

}

