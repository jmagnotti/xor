#ifndef WORLD_H
#define WORLD_H


#include <stdlib.h>
#include <map>

#include "../shape/Point3D.h"
#include "../shape/Renderable.h"
#include "../transform/Rotate.h"
#include "../event/TimerListener.h"
#include "../transform/Transform.h"
#include "../transform/Translate.h"


using namespace std;

namespace XOR {


/**
 * This is the highest-level model in the GOR framework
 */
class World : public Renderable, public TimerListener
{

public:

	/** 
	 * Destructor
	 */
	virtual ~World()
	{}


	/**
	 * Singleton accessor
	 */
	static World * GetInstance();

	
	/**
	 * Singleton accessor that also sets the high-level model. This removes all other renderables.
	 * Transforms are NOT changed. If you want to get a fresh start, call this GetInstance method, 
	 * then call setDefaults(). Note that calling setDefaults() will trash any World configuration 
	 * set by Controller.setDefaultConfiguration().
	 */
	static World * GetInstance(Renderable *);


	/**
	 * Determines if the given renderable 
	 * is the world obejct itself
	 */
	static bool IsWorldObject(Renderable *);


	/**
	 * Adds a renderable to the list with the given name.
	 * The idea is that now you can get the renderables back out
	 * of the world to perform operations on them
	 */
	void addRenderable(char * name, Renderable * rend);


	/**
	 * Clears the list of renderables
	 */
	void clean();


	/**
	 * Get the current rotation
	 */
	Rotate * getRotation();


	/**
	 * Get the current translation
	 */
	Translate * getTranslation();


	/**
	 * Returns the current Rotational Velocity of the world
	 */
	Point3D * getRotationalVelocity();


	/**
	 * Returns the current Velocity of the world
	 */
	Point3D * getVelocity();

	
	/**
	 * Performs per-step changes when activated by the timer object
	 * Shouldn't be called by non-timer objects
	 */
	void handleTick();


	/**
	 * Removes a renderable from the worlds vector
	 */
	void removeRenderable(Renderable *);


	/**
	 * Calls render on all of its subelements
	 */
	void render(void);


	/**
	 * Sets the global world rotation
	 */
	void setRotation(Rotate *);


	/**
	 * Sets the global world translation
	 */
	void setTranslation(Translate *);


protected:

	
	Point3D *   _position;
	Point3D *   _rotationalVelocity;
	Point3D *   _velocity;

	Rotate *        _rotate;
	Translate *     _translate;

	map<char*, Renderable*> renderables;

	World();
	World(Renderable * rend);


    /**
	 * Sets all of the transforms to 0.
     * Does not delete old values!
	 */
	virtual void setDefaults();

	virtual void popTransforms();
	virtual void pushTransforms();

private:

	static World * _world;

};

}

#endif			// WORLD_H
