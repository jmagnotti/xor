#ifndef SCALE_H
#define SCALE_H


#include <vector>
#include "../../include/SDL_opengl.h"

#include "../geometry/Dimension3D.h"
#include "../interpolation/InterpolationEngine.h"
#include "Transform.h"


namespace XOR {

/**
 *
 */
class Scale : public Transform
{

public:

    Scale();

    Scale(float x, float y, float z);

    Scale(Dimension3D * dimension);

    void push();

    void pushInverse();

    void clone(Scale * other);

    void set(Dimension3D * scale);
    void set(Dimension3D * scale, InterpolationEngine * interpolation);

    void increment(Dimension3D * scale);
    void increment(Dimension3D * scale, InterpolationEngine * interpolation);

    void clear();

private:

    float _xScale, _yScale, _zScale;
    vector<float*> _values;
    vector<float> _out;

};

}

#endif          // SCALE_H

