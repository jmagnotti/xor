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
#ifdef DEBUG
    //Logger::GetInstance()->decrementTabLevel();
    //Logger::GetInstance()->printTabs();
    cout << "Transform::pop()" << endl;
#endif
    
	glPopMatrix();
}

}



