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
	map<char*, Renderable*>::iterator iter   = _objects.begin();
	map<char*, Renderable*>::iterator finish = _objects.end();
	map<char*, Renderable*>::iterator prev;

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
World::World(Renderable * object)
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
World * World::GetInstance(Renderable * object)
{
	if (_world == NULL)
		_world = new World(object);

	return _world;
}


/*
 * Adds a renderable to the world
 */
void World::addObject(char * name, Renderable * object)
{
	_objects[name] = object;
}


/*
 * Get a reference to an object in the world
 */
Renderable * World::getObject(char * name)
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
bool World::IsWorldObject(Renderable * world)
{
	return (world == _world);
}


/*
 * render method
 */
void World::renderObject()
{
	map<char*, Renderable*>::iterator iter   = _objects.begin();
	map<char*, Renderable*>::iterator finish = _objects.end();

    while(iter != finish) {
        iter->second->render();
        ++iter;
    }
}

}

