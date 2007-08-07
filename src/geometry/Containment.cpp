#include "Containment.h"

namespace XOR
{

const unsigned int Containment::X =   0x00000001;
const unsigned int Containment::Y =   0x00000010;
const unsigned int Containment::Z =   0x00000100;
const unsigned int Containment::ALL = 0x00000111;
const unsigned int Containment::NIL = 0x00000000;

Containment::Containment()
{
    for (int i=0; i<3; i++) {
        _containments[i] = false;
    }
}

Containment::~Containment()
{
    delete _pointEstimate;
}

bool Containment::isContained(const int dimension)
{
    return _containments[dimension];
}

bool Containment::isXContained()
{
    return _containments[0];
}

bool Containment::isYContained()
{
    return _containments[1];
}

bool Containment::isZContained()
{
    return _containments[2];
}

void Containment::setContained(const int dimension, bool flag)
{
    _containments[dimension] = flag;
}

void Containment::setXContained(bool flag)
{
    _containments[0] = flag;
}

void Containment::setYContained(bool flag)
{
    _containments[1] = flag;
}

void Containment::setZContained(bool flag)
{
    _containments[2] = flag;
}

void Containment::setPointEstimate(Vector3D * estimate)
{
    if (_pointEstimate != NULL)
    _pointEstimate->clone(estimate);
    else
    _pointEstimate = estimate->clone();
}

Vector3D * Containment::getPointEstimate()
{
    return _pointEstimate;
}

unsigned int Containment::getContainmentMask()
{
    unsigned int mask = Containment::NIL;

    if (isXContained()) {
        //        cout << "X contained ";
        mask |= Containment::X;
    }
    if (isYContained()) {
        //        cout << "Y contained ";
        mask |= Containment::Y;
    }
    if (isZContained()) {
        //        cout << "Z contained ";
        mask |= Containment::Z;
    }

    return mask;
}

bool Containment::isFullyContained()
{
    for (int i=0; i<3; i++)
    if (!_containments[i])
    return false;

    return true;
}

void Containment::print()
{
    cout << " X is "<< (isXContained() ? "Contained" : "Not Contained");
    cout << " Y is "<< (isYContained() ? "Contained" : "Not Contained");
    cout << " Z is "<< (isZContained() ? "Contained" : "Not Contained");
    cout << endl;
}

unsigned int Containment::getInverseMask()
{
    return getContainmentMask() ^ Containment::ALL;
}

}
