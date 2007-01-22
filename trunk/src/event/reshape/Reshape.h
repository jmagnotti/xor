#ifndef RESHAPE_H
#define RESHAPE_H


#include <list>

#include "../../geometry/Dimension2D.h"
#include "ReshapeEvent.h"
#include "ReshapeListener.h"

using namespace std;

namespace XOR {

/*
 * Maintains a collection of reshape listeners that are to be notified of
 * reshape events.
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class Reshape
{

public:
    
    /**
     * Singleton Accessor
     */
    static Reshape * GetInstance();


    /**
     * sends events to listeners
     */
    virtual void fireEvent(ReshapeEvent * re)=0;


    /**
     * Builds a ReshapeEvent from the SDL_Event and then fires the event to the
     * listeners. The specification for the firing is defined by concrete children.
     */
    void generateEvent(SDL_Event * event);


    /**
     * Add a listener to the pool
     */
    void addListener(ReshapeListener * listener);


    /**
     * Remove a listener from the pool
     */
    void removeListener(ReshapeListener * listener);


protected:


    /**
     * Notifies all listeners in the pool about the current event. Only loops
     * through the collection.
     */
    void notifyListeners(ReshapeEvent * event);

    Reshape();
  
    list<ReshapeListener*> listeners;


};

}

#endif          // RESHAPE_H

