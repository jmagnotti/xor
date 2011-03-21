#ifndef COLLISIONRENDERABLE_H
#define COLLISIONRENDERABLE_H


#include "../core/Renderable.h"
#include "../object3D/Point3D.h"


namespace XOR {


/**
 * Decided to make this a subclass of Renderable, and should act again like an interface
 * The idea is that there are two kinds of graphics-- those you can collide with and those you can't
 * CollisionRenderables are still renderables and have render methods, they just also have checkCollision()
 * methods.
 *
 * @author John Magnotti, Michael Lam
 * @version 0.5
 */
class CollisionRenderable : public Renderable
{

public: 

	
	/**
     * @see Renderable
	 */
	virtual void render(void)=0;


	/** 
	 * Checks for a collision with the given point and the underlying object
	 * the function returns true upon collisions and false otherwise.
	 */
	virtual bool checkCollision(Point3D *) {    return false;   }


	/** 
	 * Checks for a collision with the given point and the underlying object on the given plane
	 * The function returns true upon collisions and false otherwise.
	 */
	//virtual bool checkCollision(Point3D*, int){return false;}


	/**
	 * Returns the class type
     * @see Renderable
	 */
	//virtual char * getRenderableType() {    return "COLLIDABLE";    }

};

}

#endif			// COLLISIONRENDERABLE_H

