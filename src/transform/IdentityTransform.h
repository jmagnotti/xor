#ifndef IDENTITYTRANSFORM_H
#define IDENTITYTRANSFORM_H

#include "Transform.h"

namespace XOR
{

/**
 * Does no modification to the glMatrix stack. Useless? Not hardly. 
 * IdentityTransform can be used as a placeholder Transform, or, more likely, 
 * as a convenient way to launch a DelayedAction on a Transformable.
 * 
 * @see DelayedAction
 * 
 * @author John Magnotti
 * @author Michael Lam
 * 
 * @verion 1.0 
 */
class IdentityTransform : public XOR::Transform
{
public:
	IdentityTransform();
	virtual ~IdentityTransform();
};

}

#endif			// IDENTITYTRANSFORM_H
