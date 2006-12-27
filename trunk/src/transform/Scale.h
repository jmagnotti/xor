#ifndef SCALE_H
#define SCALE_H


#include "Transform.h"
#include "../geometry/Dimension3D.h"


namespace XOR {

class Scale : public Transform
{

public:

    Scale()
    {}

    Scale(float a, float b, float c)
    {}

    Scale(Dimension3D * d)
    {}

    void push()
    {}

    void pushInverse()
    {}

    void clone(Scale * sc)
    {}

private:

    float _xScale, _yScale, _zScale;

};

}

#endif          // SCALE_H

