#ifndef PARTICLE_H
#define PARTICLE_H


#include "CollisionRenderable.h"
#include "Point3D.h"



namespace XOR {


/**
 * A particle is merely a point, but it has cool behavior. Be sure to 
 * initiliaze it with a list of collision renderables, so that it 
 * can check if it is colliding with anything, and show off its behavior
 */
class Particle : CollisionRenderable
{

public:

	Particle(Point3D*);

	void nextPosition();

	bool checkCollision(Point3D*);


protected:

	Point3D *	currentPosition;
	Point3D *	previousPosition;

	float		velocity[3];
	bool		alive;

};


}

#endif			// PARTICLE_H
