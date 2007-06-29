#ifndef ACTION_H
#define ACTION_H


namespace XOR {

/**
 * Provides an interface for classes that need to be run after an event
 * occurs.
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0
 */
class Action
{

public:

	/**
	 * Invoked in response to an event.
	 */
	virtual void execute()=0;

};

}

#endif			// ACTION_H

