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
	map<string, Renderable*>::iterator iter   = _objects.begin();
	map<string, Renderable*>::iterator finish = _objects.end();
	map<string, Renderable*>::iterator prev;

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
	_objects[string(name)] = object;
}


/*
 * Get a reference to an object in the world
 */
Renderable * World::getObject(char * name)
{
	return _objects[string(name)];
}


/*
 * Remove an object from the world
 */
Renderable * World::removeObject(char * name)
{
    Renderable * temp =  _objects[string(name)];

    if (temp != NULL)
        _objects.erase(string(name));

    return temp;
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
#ifdef DEBUG
    Logger::GetInstance()->printTabs();
    cout << "BEGIN RENDER LOOP" << endl;
    Logger::GetInstance()->incrementTabLevel();
#endif
    
	map<string, Renderable*>::iterator iter   = _objects.begin();
	map<string, Renderable*>::iterator finish = _objects.end();

    while(iter != finish) {
		if (iter->second != NULL)
			iter->second->render();

        ++iter;
    }
#ifdef DEBUG
    Logger::GetInstance()->decrementTabLevel();
    Logger::GetInstance()->printTabs();
    cout << "END RENDER LOOP" << endl;
#endif
}

void World::printObjectStats()
{
	map<string, Renderable*>::iterator iter   = _objects.begin();

    while(iter != _objects.end()) {
        cout << "Object name: " << iter->first 
             << ", id: "        << iter->second 
             << endl;
        ++iter;
    }

}

}

