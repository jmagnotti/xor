#ifndef WORLD_H
#define WORLD_H


#include <stdlib.h>
#include <map>

#include "../shape/Object3D.h"


using namespace std;

namespace XOR {


/**
 * This is the highest-level model in the GOR framework
 */
class World : public Object3D
{

public:


	/** 
	 * Destructor
	 */
	virtual ~World();


	/**
	 * Singleton accessor
	 */
	static World * GetInstance();

	
	/**
	 * Singleton accessor that also sets the high-level model. This removes all other renderables.
	 * Transforms are NOT changed. If you want to get a fresh start, call this GetInstance method, 
	 * then call clear. Note that calling setDefaults() will trash any World configuration 
	 * set by Controller.setDefaultConfiguration().
	 */
	static World * GetInstance(Object3D *);


	/**
	 * Determines if the given renderable 
	 * is the world obejct itself
	 */
	static bool IsWorldObject(Object3D * world);


	/**
	 * Adds a renderable to the list with the given name.
	 * The idea is that now you can get the renderables back out
	 * of the world to perform operations on them
	 */
	void addObject(char * name, Object3D * object);


	/**
	 * Clears the list of renderables
	 */
	void clean();


	/**
	 * Returns a reference to a named renderable.
	 */
	Object3D * getObject(char *);


	/**
	 * Removes a renderable from the worlds vector
	 */
	void removeObject(char *);


	/**
	 * Display the world
	 */
	void render();
	
	void renderObject(){render();}


	/**
	 * soon to be handled by Obj3D?
	 */
	Dimension3D * getDimension() {return new Dimension3D(0,0,0);}


	/**
	 * soon to be handled by Obj3D?
	 */
	Vector3D * getBaseVector() {return new Vector3D(0,0,0);}


private:

	World();
	World(Object3D * object);

	static World * _world;
	map<char*, Object3D*> _objects;

};

}

#endif			// WORLD_H

