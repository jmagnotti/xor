#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H


#include <algorithm>
#include <vector>
#include "Transform.h"

#include "Translate.h"

using namespace std;

namespace XOR {

/**
 * A new way to do Transforms. Object gains transformation ability through
 * decoration. The actual decoration is deferred to subclasses of
 * Transformable. This allows for the transformation of different kinds of
 * objects (e.g., Transformable3D, Transformable2D). This class merely
 * provides a common place for adding, applying, and removing Transforms,
 * and should be treated as a mixin. This is very different from previous
 * versions of Transformable that may have applied transforms
 * automatically - subclasses must explicity call doTransform and
 * undoTransform appropriately.
 *
 * Transforms should only be applied by the child class,
 * which is why the do & undo methods are protected.
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.1
 */
class Transformable
{

public:

	/**
	 * Adds a transform to the top of the stack.
	 */
    void addTransform(Transform * transform);

	/**
	 * Removes the given transform from the stack, if it exists.
	 */
    void removeTransform(Transform * transform);


protected:

	/**
	 * Can't create Transformables
	 */
	Transformable();

	/**
	 * This applies the transform stack. It is left virtual in case special
	 * processing needs to be done.
	 */
    virtual void doTransform();

	/**
	 * This removes the transform stack. It is left virtual in case special
	 * processing needs to be done.
	 */
    virtual void undoTransform();

	/**
	 * This applies the inverse transform stack (T * Tinv = I). It is
	 * left virtual in case special processing needs to be done.
	 */
    virtual void doInverseTransform(); 

    vector<Transform*> _transforms;
    
private:
	
	static int _transformCount;

};

}

#endif			// TRANSFORMABLE_H

