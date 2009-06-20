#include "Object2DCollection.h"


namespace XOR {

Object2DCollection::Object2DCollection()
{}

Object2DCollection::~Object2DCollection()
{
	//TODO delete everything in the collection

}

/**
 * Adds an object to the collection. This collection does not allow duplicates. Matching is done based on pointer address only.
 */
void Object2DCollection::addObject2D(Object2D * object)
{
    _objects[object] = object;
}


/**
 * Removes the object from the collection and returns a reference to it. If the object was not in the collection, NULL is returned. The caller is responsible for memory associated with the parameter and the return value (check for NULL before deleting).
 */
Object2D * Object2DCollection::removeObject(Object2D * object)
{
    map<Object2D*,Object2D*>::iterator found =  _objects.find(object);
    Object2D * removed = NULL;

    // object was in the collection
    if (found != _objects.end()) {
        removed = found->first;
        _objects.erase(found);
    }

    return removed;
}


/**
 * Unordered rendering of the objects
 */
void Object2DCollection::renderObject()
{
    map<Object2D*,Object2D*>::iterator iter   = _objects.begin();
    map<Object2D*,Object2D*>::iterator finish = _objects.end();

    while(iter != finish) {
        //saves us from to set the 2D state over and over
        iter->second->renderObject();
        ++iter;
    }
}

Dimension2D * Object2DCollection::getDimension()
{
    return new Dimension2D(0,0);
}

Vector2D * Object2DCollection::getBaseVector()
{
    return new Vector2D(0,0);
}

}

