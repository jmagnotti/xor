#include "Scale.h"

namespace XOR {

/*
 *
 */
Scale::Scale()
{
    // very important that the scalars don't get set to 0 || NULL
    _xScale = _yScale = _zScale = 1.0f;

    _values.push_back(&_xScale);
    _values.push_back(&_yScale);
    _values.push_back(&_zScale);
}


/*
 *
 */
Scale::Scale(float x, float y, float z)
{
    _xScale = x;
    _yScale = y;
    _zScale = z;

    _values.push_back(&_xScale);
    _values.push_back(&_yScale);
    _values.push_back(&_zScale);
}


/*
 *
 */
Scale::Scale(Dimension3D * dimension)
{
    _xScale = dimension->getX();;
    _yScale = dimension->getY();
    _zScale = dimension->getZ();

    _values.push_back(&_xScale);
    _values.push_back(&_yScale);
    _values.push_back(&_zScale);
}


/*
 *
 */
void Scale::set(Dimension3D * scale)
{
    _xScale = scale->getX();
    _yScale = scale->getY();
    _zScale = scale->getZ();
}


void Scale::set(Dimension3D * scale, InterpolationEngine * interpolation)
{
    _out.clear();

    _out.push_back(scale->getX());
    _out.push_back(scale->getY());
    _out.push_back(scale->getZ());

    interpolation->setup(_values, _out);
    interpolation->start();
}

void Scale::increment(Dimension3D * scale)
{
    _xScale += scale->getX();
    _yScale += scale->getY();
    _zScale += scale->getZ();
}

/*
 *
 */
void Scale::increment(Dimension3D * scale, InterpolationEngine * interpolation)
{
    _out.clear();

    _out.push_back(scale->getX() + _xScale);
    _out.push_back(scale->getY() + _yScale);
    _out.push_back(scale->getZ() + _zScale);
    
    interpolation->setup(_values, _out);
    interpolation->start();
}


/*
 *
 */
void Scale::push()
{
    glPushMatrix();
        glScalef(_xScale, _yScale, _zScale);
}

/*
 *
 */
void Scale::pushInverse()
{
    glPushMatrix();
        glScalef(1.0/_xScale, 1.0/_yScale, 1.0/_zScale);
}

/*
 *
 */
void Scale::clone(Scale * other)
{
    _xScale = other->_xScale;
    _yScale = other->_yScale;
    _zScale = other->_zScale;
}

/*
 * set all scalars to 1
 */
void Scale::clear()
{
    _xScale = _yScale = _zScale = 1.0f;
}

}

