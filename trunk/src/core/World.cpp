#include "World.h"


namespace XOR {

// set the static instance to null 
World *	World::_world = 0;


/* 
 * Default Constructor
 */
World::World()
{}

World::~World()
{
	map<char*, Object3D*>::iterator iter   = _objects.begin();
	map<char*, Object3D*>::iterator finish = _objects.end();
	map<char*, Object3D*>::iterator prev;

    while(iter != finish) {
        prev = iter;
        ++iter;
        delete prev->second;
    }

    _objects.clear();
}

/* 
 * Explicit Constructor
 */
World::World(Object3D * object)
{
	addObject("world", object);
}


/* 
 * Returns an instance
 */
World * World::GetInstance()
{
	if (_world == NULL)
		_world = new World();

	return _world;
}


/*
 * Returns an instance initialized with the given object, unless the world has
 * already been initialized
 */
World * World::GetInstance(Object3D * object)
{
	if (_world == NULL)
		_world = new World(object);

	return _world;
}


/*
 * Adds a renderable to the world
 */
void World::addObject(char * name, Object3D * object)
{
	_objects[name] = object;
}


/*
 * Get a reference to an object in the world
 */
Object3D * World::getObject(char * name)
{
	return _objects[name];
}


/*
 * Remove an object from the world
 */
void World::removeObject(char * name)
{
	_objects.erase(name);
}


/**
 * Remove all renderables from the world
 */
void World::clean()
{
	_objects.clear();
}


/*
 * Returns if the given object is the world object
 */
bool World::IsWorldObject(Object3D * world)
{
	return (world == _world);
}


/*
 * render method
 */
void World::renderObject()
{
	map<char*, Object3D*>::iterator iter   = _objects.begin();
	map<char*, Object3D*>::iterator finish = _objects.end();

    while(iter != finish) {
        iter->second->render();
        ++iter;
    }
}

}

