#include "World.h"


namespace XOR {

// set the static instance to null
World *	World::_world = 0;


/* 
 * Default Constructor
 */
World::World()
{
	setDefaults();
}


/* 
 * Explicit Constructor
 */
World::World(Renderable * rend)
{
	setDefaults();
	addRenderable("world", rend);
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
 * Returns an instance initialized with
 * the given renderable
 */
World * World::GetInstance(Renderable *rend)
{
	if (! (_world == NULL)) {
		_world->clean();
		_world->addRenderable("world", rend);
	}
	else {
		_world = new World(rend);
	}

	return _world;
}


/*
 * Adds a renderable to the world
 */
void World::addRenderable(char * name, Renderable * rend)
{
	renderables[name] = rend;
}


/**
 * Remove all renderables from the world
 */
void World::clean()
{
	renderables.clear();
}


/* 
 * return global rotation
 */
Rotate * World::getRotation()
{
	return _rotate;
}


/*
 * return global translation
 */
Translate * World::getTranslation()
{
	return _translate;
}


/* 
 * Handles timer updates
 */
void World::handleTick()
{
	_translate->increment(_velocity);
	_rotate->increment(_rotationalVelocity);
}


/*
 * Returns if the given object is the world object
 */
bool World::IsWorldObject(Renderable *rend)
{
	bool result;

	if (_world == NULL)
		result = false;
	else
		result = (rend == _world);

	return result;
}


/* 
 * Removes transforms
 */
void World::popTransforms()
{
	_translate->pop();
	_rotate->pop();
}


/*
 * applies transforms
 */
void World::pushTransforms()
{
	// order does matter
	_rotate->push();
	_translate->push();
}


/* 
 * calls render
 */
void World::render(void)
{
	pushTransforms();

	map<char*, Renderable*>::iterator iter	 = renderables.begin();
	map<char*, Renderable*>::iterator finish = renderables.end();

	while(iter != finish) {
		iter->second->render();
		++iter;
	}

	popTransforms();
}


/* 
 * Returns the world to a pleasant default state
 */
void World::setDefaults()
{
	_position			= new Point3D	(0,0,0);

	_rotationalVelocity = new Point3D	(0,0,0);
	_velocity			= new Point3D	(0,0,0);

	_rotate				= new Rotate	(0,0,0,0);
	_translate			= new Translate	(0,0,0);
}


/*
 * set rotation
 */
void World::setRotation(Rotate *rot)
{
	_rotate = rot;
}


/* 
 * set translation
 */
void World::setTranslation(Translate *tran)
{
	_translate = tran;
}

}

