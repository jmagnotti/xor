#ifndef HITLISTENER_H
#define HITLISTENER_H

#include "Brick.h"

class Brick;

/**
 * The HitListener interface guarantees that any class implementing it will have a 
 * handle hit method that determines the object behavior when it receives a hit.
 * To be more generic it would make sense to pass in a hittable object to handleHit
 * but for this version, it will take a brick object.
 */

class HitListener
{
    public:
        /**
         * This method will receive . 
         * 
         * @param brick - the brick that was hit
         */
        virtual void handleHit(Brick * brick) = 0;
};
#endif

