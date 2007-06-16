#ifndef MOUSESKELETON_H
#define MOUSESKELETON_H


#include <stdlib.h>
#include <list>

#include "../../../include/SDL_Thread.h"
#include "../../multicast/MulticastSocket.h"
#include "../../multicast/MulticastSocketPool.h"

#include "Mouse.h"
#include "MouseEvent.h"
#include "MouseClickEvent.h"
#include "MouseMotionEvent.h"
#include "MouseEventFactory.h"


using namespace std;

namespace XOR {

/**
 * 
 */
class MouseSkeleton : public Mouse
{

public:

    virtual ~MouseSkeleton();

	/**
	 * Fires an event to listeners
	 */
	void fireEvent(MouseEvent * me);


	/**
	 * Singleton Constructor
	 */
	static MouseSkeleton * GetInstance(void);

	static int Listen(void * data);


private:

    MouseSkeleton();

	static MouseSkeleton * _mouseSkeleton;
	static MulticastSocket * _socket;
	static bool _keepGoing;

	SDL_Thread * _thread;
};

}

#endif			//MOUSESKELETON_H

