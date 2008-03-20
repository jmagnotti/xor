#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Vector3D.h"

namespace XOR
{

/**
 * Stores state information about the containment relationship of two objects. 
 * Used for passing information about bounds checking.
 * 
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.0 
 */
class Containment
{

public:

    // Do not use the constants in Vector3D, as they are 0-based. 
    // Since we are &ing these later, they are different.
    //static const unsigned int X;
    //static const unsigned int Y;
    //static const unsigned int Z;
    //static const unsigned int NIL;
    //static const unsigned int ALL;

#define CONTAINMENT_X 0x00000001
#define CONTAINMENT_Y 0x00000010
#define CONTAINMENT_Z 0x00000100
#define CONTAINMENT_ALL 0x00000111
#define CONTAINMENT_NIL 0x00000000

    Containment();

    virtual ~Containment();

    void setXContained(bool flag);
    void setYContained(bool flag);
    void setZContained(bool flag);

    /**
     * dimensions here should be accessed using Vector3D::{X|Y|Z}
     */
    void setContained(const int dimension, bool flag);

    bool isXContained();
    bool isYContained();
    bool isZContained();

    /**
     * dimensions here should be accessed using Vector3D::{X|Y|Z}
     */
    bool isContained(const int dimension);

    void setPointEstimate(Vector3D * estimate);

    Vector3D * getPointEstimate();

    unsigned int getContainmentMask();

    /**
     * A mask with 1 for dimensions that are NOT contained.
     * 
     * @return getContainmentMask() ^ Containment::ALL
     */
    unsigned int getInverseMask();

    bool isFullyContained();

    void print();

private:

    bool _containments[3];

    Vector3D * _pointEstimate;

};

}

#endif          // INTERSECTION_H
