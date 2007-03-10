#ifndef OBJECT3DCOLLECTION_H
#define OBJECT3DCOLLECTION_H


#include <map>
#include "Object3D.h"
#include "CompiledObject3D.h"


using namespace std;

namespace XOR {

/**
 *
 */
class Object3DCollection : public Object3D
{

public:

    
    /**
     * Default Constructor.
     */
    Object3DCollection();


    /**
     * Adds an object to the collection. This collection does not allow
     * duplicates. Matching is done based on pointer address only.
     */
    virtual void addObject3D(Object3D * object);


    /**
     * Removes the object from the collection and returns a reference to it. If
     * the object was not in the collection, NULL is returned. The caller is
     * responsible for memory associated with the parameter and the return
     * value (check for NULL before deleting).
     */
    Object3D * removeObject(Object3D * object);


    /**
     * Renders each object in the collection with no ordering.
     */
    void renderObject();


    /**
     * Compiles the list into a holistic display list. Objects that were in the
     * collection are discarded. The memory associated with those objects
     * remains.
     */
    void compile();


    Vector3D * getBaseVector();

    Dimension3D * getDimension();

protected:

	map<Object3D*,Object3D*> _objects;

};

}

#endif			// OBJECT3DCOLLECTION_H

