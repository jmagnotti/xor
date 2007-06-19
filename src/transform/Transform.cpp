#include "Transform.h"

namespace XOR {

Transform::Transform()
{}
	
/**
 * Removes the transform. Child classes can override this behavior,
 * but most will just use it. 
 */
void Transform::pop(void)
{
	cout << "popping" << endl;
	glPopMatrix();
}

}

