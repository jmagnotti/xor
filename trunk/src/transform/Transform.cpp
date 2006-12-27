#include "Transform.h"

namespace XOR {

	
/**
 * Removes the transform. Child classes can override this behavior,
 * but most will just use it. 
 */
void Transform::pop(void)
{
	glPopMatrix();
}

}

