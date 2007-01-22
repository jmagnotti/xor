#ifndef RESHAPELISTENER_H
#define RESHAPELISTENER_H


#include "ReshapeEvent.h"


namespace XOR {

/**
 * The implementer of this class is responsible for knowing what to do when the 
 * window is resized.
 */
class ReshapeListener
{

public:
    
    /**
     * Implement the SDL version of reshape events
     */
    virtual void handleReshape(ReshapeEvent * event)=0;

};

}

#endif          // RESHAPELISTENER_H

