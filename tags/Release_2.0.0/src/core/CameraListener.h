#ifndef CAMERALISTENER_H
#define CAMERALISTENER_H


#include "../geometry/Vector3D.h"


namespace XOR {

/**
 * Interface for classes that want to be informed of camera movements.
 */
class CameraListener
{

public:

    /**
     * Called whenever the camera's position changes This Vector3D is shall not
     * be an alias to the camera's actual position. Listeners shall not modify
     * this variable, as it will affect others down the chain. This vector
     * should also not be aliased or retained, as it is destroyed by the
     * caller. The memory is deallocated by this thread however, so cloning the
     * vector is only necessary if you wish to store the points.
     *
     * @param position The new camera position
     */
	virtual void handleCameraMove(Vector3D * position)=0;

};

}

#endif		// CAMERALISTENER_H

