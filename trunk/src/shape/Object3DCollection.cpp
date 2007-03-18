#include "Object3DCollection.h"


namespace XOR {

Object3DCollection::Object3DCollection()
{}


/**
 * Adds an object to the collection. This collection does not allow duplicates. Matching is done based on pointer address only.
 */
void Object3DCollection::addObject3D(Object3D * object)
{
    _objects[object] = object;
}


/**
 * Removes the object from the collection and returns a reference to it. If the object was not in the collection, NULL is returned. The caller is responsible for memory associated with the parameter and the return value (check for NULL before deleting).
 */
Object3D * Object3DCollection::removeObject(Object3D * object)
{
    map<Object3D*,Object3D*>::iterator found =  _objects.find(object);
    Object3D * removed = NULL;

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
void Object3DCollection::renderObject()
{
    map<Object3D*,Object3D*>::iterator iter   = _objects.begin();
    map<Object3D*,Object3D*>::iterator finish = _objects.end();

    while(iter != finish) {
        iter->second->render();
        ++iter;
    }
}

Dimension3D * Object3DCollection::getDimension()
{
    return new Dimension3D(0,0,0);
}

Vector3D * Object3DCollection::getBaseVector()
{
    return new Vector3D(0,0,0);
}


void Object3DCollection::compile(bool destroy)
{
    CompiledObject3D * obj = new CompiledObject3D(this);

    if (destroy) {
        Object3D * temp;
        map<Object3D*,Object3D*>::iterator iter   = _objects.begin();
        map<Object3D*,Object3D*>::iterator finish = _objects.end();

        while(iter != finish) {
            temp = iter->first;
            ++iter;
            delete temp;
        }
    }
    _objects.clear();
    _objects[obj] = obj;
}

}

