#ifndef ACTION_H
#define ACTION_H


#include "../../xor.h"


using namespace XOR;


/**
 * Should behave like an interface. Allows for generic treatment of all
 * user defined actions in the gui. All user defined actions should extend
 * this class.
 */
class Action
{

public:

    /**
     * Called by the GUI to execute the method contained in the user-defined
     * action. If the action results in an event being fired, the method may 
     * be called from a separate thread such as the SDL event loop.
     */
    virtual void performAction()=0;


};


#endif ACTION_H       // ACTION_H

