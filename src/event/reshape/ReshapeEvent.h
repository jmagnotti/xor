#ifndef RESHAPEEVENT_H
#define RESHAPEEVENT_H


#include "../../../include/SDL.h"
#include "../../geometry/Dimension2D.h"


namespace XOR {


/**
 * Encapsulates the new dimensions of the window. Note that this does not
 * enforce that the window is actually this size. Also, the values in a given
 * reshape event are not guaranteed to persistent, and should be cloned, not
 * aliased, if they need to be stored. Calling getHeight and getWidth is
 * sufficient, just don't alias the ReshapeEvent itself.
 *
 * Do not delete the reshape event, its instance persists throughout program
 * execution. If it is deleted, it may affect other ReshapeListeners.
 */
class ReshapeEvent
{

public:


    /**
     * Used to construct a reshape event from the SDL_Event.
     */
    static ReshapeEvent * ConstructInstance(SDL_Event * event);


    /**
     * Used to construct a reshape event from a Dimension2D object.
     */
    static ReshapeEvent * ConstructInstance(Dimension2D * size);


    /**
     * Returns the height of the new window dimension, in pixels.
     */
    int getHeight();


    /**
     * Returns the width of the new window dimension, in pixels.
     */
    int getWidth();


private:

    ReshapeEvent();

    ReshapeEvent(Dimension2D * size);

    Dimension2D * _size;

    void initialize(Dimension2D * size);

    static ReshapeEvent * _reshapeEvent;

};

}

#endif          // RESHAPEEVENT_H

