#include "Particle.h"

namespace XOR {

/*
 * Explicit Constructor
 */
Particle::Particle(Vector3D * position)
{
	currentPosition = position;
}


bool Particle::checkCollision(Vector3D*)
{
	return false;
}


/*
 * One step of animation
void psTimeStep(PSparticle* p, float dt)
{
    if (p->alive)
	{
		p->velocity[0] += 0;
		p->velocity[1] += PS_GRAVITY*dt;
		p->velocity[2] += 0;

		p->previous[0] = p->position[0];
		p->previous[1] = p->position[1];
		p->previous[2] = p->position[2];

		p->position[0] += p->velocity[0]*dt;
		p->position[1] += p->velocity[1]*dt;
		p->position[2] += p->velocity[2]*dt;
	}

}
*/

}

