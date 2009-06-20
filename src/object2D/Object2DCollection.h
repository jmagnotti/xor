#ifndef OBJECT2DCOLLECTION_H
#define OBJECT2DCOLLECTION_H


#include <SDL/SDL_opengl.h>
#include <map>

#include "Object2D.h"

namespace XOR {

/**
 *
 */
class Object2DCollection : public Renderable
{

public:

    
    /**
     * Default Constructor.
     */
    Object2DCollection();
    ~Object2DCollection();


    /**
     * Adds an object to the collection. This collection does not allow
     * duplicates. Matching is done based on pointer address only.
     */
    virtual void addObject2D(Object2D * object);


    /**
     * Removes the object from the collection and returns a reference to it. If
     * the object was not in the collection, NULL is returned. The caller is
     * responsible for memory associated with the parameter and the return
     * value (check for NULL before deleting).
     */
    Object2D * removeObject(Object2D * object);


    /**
     * Renders each object in the collection with no ordering.
     */
    void renderObject();


    /**
     * Compiles the list into a holistic display list. Objects that were in the
     * collection are discarded. The memory associated with those objects
     * remains.
     * @destroy If the enderables in the collection should be 'deleted'
     */
    void compile(bool destroy=false);


    Vector2D * getBaseVector();

    Dimension2D * getDimension();

protected:

	map<Object2D*,Object2D*> _objects;

};

}

#endif			// OBJECT2DCOLLECTION_H

