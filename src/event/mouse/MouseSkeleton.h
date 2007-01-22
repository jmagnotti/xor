#ifndef MOUSESKELETON_H
#define MOUSESKELETON_H


#include "../../../include/SDL.h"

#include <stdlib.h>
#include <list>

#include "MouseEvent.h"
#include "MouseEventFactory.h"
#include "MouseClickEvent.h"
#include "MouseMotionEvent.h"


using namespace std;

namespace XOR {

/**
 * 
 */
class MouseSkeleton : public Mouse
{

public:


	/**
	 * Fires an event to listeners
	 */
	void fireEvent(MouseEvent * me);


	/**
	 * Singleton Constructor
	 */
	static MouseSkeleton * GetInstance(void);


private:

    MouseSkeleton();

	static MouseSkeleton * _mouseSkeleton;

};

}

#endif			//MOUSESKELETON_H

