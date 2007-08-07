#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <vector>
#include <list>
#include <iostream>
#include <stdio.h>

#include "Transform.h"
#include "Translate.h"
#include "Rotate.h"
#include "../geometry/Containment.h"
#include "OrientationListener.h"
#include "../event/ContinuousAction.h"
#include "../geometry/Dimension3D.h"

using namespace std;

namespace XOR
{

class ContinuousAction;

/**
 * Easy way to have holistic positioning of an object. Tries to be 'last transform you'll ever need.' 
 * 
 * Be sure to read method-specific comments.
 *  
 * Should be updated to use Quaternions | Eigenaxes.
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.1
 */
class Orientation : public Transform
{

public:

    /**
     * Explicit Constructor
     */
    Orientation();

    ~Orientation();

    Orientation(Translate * position, Rotate * roll, Rotate * theta,
                Rotate * phi);

    /**
     * Explicit Constructor
     */
    Orientation(Translate * position, Vector3D * focalPoint);

    /**
     * @see Transform
     */
    void push();

    void clone(Orientation * other);

    /**
     * Returns a new Orientation whose values are equivalent.
     */
    Orientation * clone();

    /**
     * Calls the inverse method on each transform contained by the
     * orientation. This is (almost) never appropriate.
     */
    void pushInverse();

    /**
     * debug transform info
     */
    void print();

    /**
     * @see Transform
     */
    void pop();

    /**
     * @see Transform
     */
    void toIdentity();

    /**
     * @see Transform
     */
    void transform(Vector3D * position);
    void transform(Vector2D * position);

    /**
     * @see Transform
     */
    void transform(Dimension3D * size);
    void transform(Dimension2D * size);

    /**
     * Increments the objects world position in the current direction
     * (supply a negative number to go in the opposing direction) of the
     * focal vector.
     */
    void moveAlongFocalVector(float distance);

    /**
     * Increments the objects world position in the current direction
     * (supply a negative number to go in the reverse direction) of the
     * focal vector. Uses getCurrentWalkIncrement() to determine the
     * distance to move.
     */
    void moveAlongFocalVector();

    /**
     * Drags the object back along the focal vector (or ahead if a negative
     * value was supplied to moveAlongFocalVector), Using the magnitude of
     * the previous movement. Used mainly as a way to undo camera
     * movements. Note that this doesn't take into account any translations
     * that are in effect. Neither does it call stopMovingAlongFocalVector,
     * but it is recommended that calling classes be aware of whether the
     * object is currently being auto-walked.
     */
    void moveBackAlongFocalVector();

    /**
     * Starts incrementing the position of the object in response to timer
     * ticks. This behavior continues until stopMovingAlongFocalVector is
     * called. Implementation is handled by MovementHelper, located in
     * Orientation.cpp.
     *
     * If the object has already been "started," the effect is additive,
     * which will allow multiple objects to impact the camera's speed
     * independently.
     */
    void startMovingAlongFocalVector();

    /**
     * Returns the current walk velocity.
     */
    float getWalkVelocity();

    /**
     * Returns the current walk velocity step. This is the value that will
     * be used if startMovingAlongFocalVector or moveAlongFocalVector is
     * called without specifying the actual parameters.
     */
    float getCurrentWalkIncrement();

    /**
     * Sets the current walk velocity step. This is the value that will
     * be used if startMovingAlongFocalVector or moveAlongFocalVector is
     * called without specifying the actual parameters.
     */
    void setCurrentWalkIncrement(float distance);

    /**
     * Adds a specific amount to the "walk"
     */
    void startMovingAlongFocalVector(float distance);

    /**
     * Stops incrementing the position of the object.
     */
    void stopMovingAlongFocalVector();

    /**
     * Reduces a certain amount of the "walk"
     */
    void stopMovingAlongFocalVector(float distance);

    Vector3D * getPosition();

    void setPosition(Vector3D * position);
    void incrementPosition(Vector3D * position);

    float getRoll();
    float getPitch();
    float getYaw();

    void setRoll(float angle);
    void setPitch(float angle);
    void setYaw(float angle);

    void incrementRoll(float angle);
    void incrementPitch(float angle);
    void incrementYaw(float angle);

    void setFocalPoint(Vector3D * focalPoint);

    // interpolated transforms

    //void setRoll(float angle, int milliseconds);
    //void setPitch(float angle, int milliseconds);
    //void setYaw(float angl, int milliseconds);
    //
    void incrementRoll(float angle, int milliseconds);
    void incrementPitch(float angle, int milliseconds);
    void incrementYaw(float angl, int milliseconds);
    //
    //void setPosition(Vector3D * position, int milliseconds);
    void incrementPosition(Vector3D * position, int milliseconds);
    //void setFocalPoint(Vector3D * focalPoint, int milliseconds);

    //float  getFocalDistance();
    //Vector3D * getFocalPoint() const;


    void addListener(OrientationListener * listener);
    void removeListener(OrientationListener * listener);

protected:

    void notifyPositionChange(Vector3D * delta, Vector3D * newPosition);

    void notifyRotationChange(float newAngle, const Vector3D * axis);

private:

    //void updateFocalPoint();

    //void updateFromFocalPoint();

    vector<Rotate*> _pitch;
    vector<Rotate*> _yaw;
    vector<Rotate*> _roll;
    vector<Translate*> _position;

    bool _translated;
    bool _hasPitch, _hasYaw, _hasRoll;

    ContinuousAction * _action;
    float _currentWalkIncrement;

    list<OrientationListener*> _listeners;

    //Rotate    * _roll, * _theta, * _phi;
    //Translate * _position;

    //Vector3D  * _focalPoint;

    //float _focalDistance;
};

}

#endif          // ORIENTATION_H
