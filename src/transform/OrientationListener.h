#ifndef ORIENTATIONLISTENER_H
#define ORIENTATIONLISTENER_H

namespace XOR
{

/**
 * Interface for classes that want to be informed of changes to an Orientation object.
 * 
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0
 */
class OrientationListener
{

public:

    /**
     * Called whenever an Orientation's position changes This Vector3D shall not
     * be an alias to the an Orientation's actual position. Listeners should not
     * modify  this variable, however,  as it will affect others down the
     * chain. This vector should be neither aliased nor retained, as it is
     * destroyed by the caller. The memory is deallocated in the calling
     * thread however, so  cloning the vector is only necessary if you wish
     * to store the points.
     *
     * If the caller 'disagrees' with the proposed new position, return
     * the index of the offending dimension(s). For example, if the object
     * has outstepped its bound in the X dimension, then  returning
     * Containment::X would nullify that portion of the  movement. Once the
     * move has been nullified, it can not be  undone. Further more, if all
     * dimensions have been nullified,  this method is not called on future
     * listeners, as the object  is no longer moving. This may have some
     * issues with trying  to play sounds or other position-neutral events.
     * 
     * A note on nullifying multiple dimensions at once: 
     *  Orientation is going to check the return value against constants defined
     *  in Containment.h. This means that you can | them together to specify 
     *  multiple null targets. Containment::X | Containment::Y. Some objects
     *  will provide an Containment object, from which you can call 
     *  Containment::getMask(). 
     * 
     * @see Containment
     * 
     * There is a temptation to just have this return a Containment object.
     *
     * @param position The new position of the object
     * @return The dimension to nullify, or -1 if no change is required.
     */
    virtual int handlePositionChange(Vector3D * position)=0;

    /**
     * 
     */
    virtual void handleRotationChange(float angle, const Vector3D * axis)=0;

};

}

#endif		// ORIENTATIONLISTENER_H 
