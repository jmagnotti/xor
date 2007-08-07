#ifndef ROTATE_H
#define ROTATE_H

#include <vector>
#include <iostream>
#include <stdio.h>

#include "Transform.h"

#include "Translate.h"
#include "../event/timer/Timer.h"
#include "../geometry/Dimension3D.h"
#include "../geometry/Vector2D.h" 
#include "../geometry/Dimension2D.h"
#include "../event/Action.h"
#include "../interpolation/Interpolator.h"
#include "../interpolation/InterpolatorFactory.h"
#include "../util/GraphicsConversionUtility.h"

using namespace std;

namespace XOR
{

/**
 * Applies a rotate transform. The constructors allow for arbitrary centers of
 * rotation, instead of assuming the origin. To visualize the rotation, imagine
 * a line drawn from the origin (or the specified center) to the point
 * specified by axis param or by [x, y, z]. The Rotation will effectively
 * mirror an object across the newly formed line.
 * 
 * @see Transform
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.1
 */
class Rotate : public Transform
{

public:

    static const Vector3D * ROLL;
    static const Vector3D * PITCH;
    static const Vector3D * YAW;
    static const Vector3D * ORIGIN;

    /**
     * Default Constructor
     */
    Rotate();
    virtual ~Rotate();

    /**
     * Explicit Constructors for immediate translations
     */
    static Rotate * CreateRotate(float angle, const Vector3D * axis,
                                 const Vector3D * center=ORIGIN);

    static Rotate * CreateRotate(float angle, float x, float y, float z,
                                 const Vector3D * center=ORIGIN);

    /** 
     * I am not sure there is a clear semantic for when to use Actions in
     * ImmediateRotates. Should the Action be fired after first push? If so,
     * the action will occur before any change is seen -- this may not be the
     * expected behavior, as the user may want something to happen
     * sequentially.  They could be delayed to happen on the second push, that
     * seems to arbitrary to implement.  
     */
    //static Rotate * CreateRotate(float angle, Vector3D * axis, Action * action);
    //static Rotate * CreateRotate(float angle, float x, float y, float z, Action * action);


    /**
     * Explicit Constructors for interpolated translations
     */
    static Rotate * CreateRotate(float angle, const Vector3D * axis,
                                 int milliseconds,
                                 const Vector3D * center=ORIGIN);

    static Rotate * CreateRotate(float angle, const Vector3D * axis,
                                 int milliseconds, Action * action,
                                 const Vector3D * center=ORIGIN);

    static Rotate * CreateRotate(float angle, float x, float y, float z,
                                 int milliseconds,
                                 const Vector3D * center=ORIGIN);

    static Rotate * CreateRotate(float angle, float x, float y, float z,
                                 int milliseconds, Action * action,
                                 const Vector3D * center=ORIGIN);

    /**
     * Clones the values from one rotate to another
     */
    void clone(Rotate *);

    /**
     * Applies the rotation to the current transform stack
     */
    void push(void);

    /**
     * removes the effect of rotation. Needed so we can pop the centering translation
     */
    void pop(void);

    /**
     * Applies the reverse rotation, such that T * Tinv = I
     */
    void pushInverse(void);

    /**
     * Direct access to the angle of rotation.
     */
    void setAngle(float angle);

    /**
     * reset the rotate to have no effect
     */
    void toIdentity();

    // TODO Implement these in Rotate.cpp
    void transform(Vector3D * position);
    void transform(Dimension3D * size);

    void transform(Vector2D * position);
    void transform(Dimension2D * size);
    //--

    /**
     * 
     */
    void print();

    /**
     * accessor for easier transforming (see Orientation implementation)
     */
    float getAngle();

protected:

    //FIXME is this necessary?
//    friend class Orientation;

    float _xCoord, _yCoord, _zCoord;
    float _angle;

    Rotate(float angle, float x, float y, float z, const Vector3D * center);

    Rotate(float angle, const Vector3D * axis, const Vector3D * center);

    Translate * _centeringTranslate;
    const Vector3D * _center;

    static int stackDepth;

};

class InterpolatedRotate : public Rotate
{

public:

    ~InterpolatedRotate();

    InterpolatedRotate(float angle, const Vector3D * axis, int milliseconds,
                       const Vector3D * center);

    InterpolatedRotate(float angle, const Vector3D * axis, int milliseconds,
                       Action * action, const Vector3D * center);

    InterpolatedRotate(float angle, float x, float y, float z,
                       int milliseconds, const Vector3D * center);

    InterpolatedRotate(float angle, float x, float y, float z,
                       int milliseconds, Action * action,
                       const Vector3D * center);

    void push();

    void pushInverse();

private:
    /**
     * advances the interpolation and fires the action (if there is one) on
     * completion (_remaining <= 0)
     */
    void interpolate(void);

    void build(float target, int milliseconds, Action * action);

    float _target;

    int _remaining, _total;

    vector<float> * _steps;
    Action * _action;

};

class ImmediateRotate : public Rotate
{

public:

            ImmediateRotate(float angle, const Vector3D * axis,
                            const Vector3D * center);
    ImmediateRotate(float angle, float x, float y, float z,
                    const Vector3D * center);

};

}

#endif			// ROTATE_H
