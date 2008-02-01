#include "Scale.h"

namespace XOR {
/*
 *
 */
Scale::Scale()
{
    // very important that the scalars don't get set to 0 || NULL
    //_xScale = _yScale = _zScale = 1.0f;

	//fillVector();
}


Scale::~Scale()
{}

/*
 *
 */
Scale::Scale(float x, float y, float z)
{
    _xScale = x;
    _yScale = y;
    _zScale = z;
}


/*
 *
 */
Scale::Scale(Vector3D * scalar)
{
    _xScale = scalar->getX();;
    _yScale = scalar->getY();
    _zScale = scalar->getZ();

}



/*
 *
 */
void Scale::push()
{
	#ifdef DEBUG
		cout << "Scale::push()" << endl;
	#endif

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
 * scalars in Vector3D form
 */
Vector3D * Scale::toVector()
{
	return new Vector3D(_xScale, _yScale, _zScale);
}

/*
 * set all scalars to 1
 */
void Scale::toIdentity()
{
    _xScale = _yScale = _zScale = 1.0f;
}

void Scale::print()
{
    cout << "x: " << _xScale << ", y: " << _yScale 
         << ", z: " << _zScale << endl;
}
//TODO implement
    void Scale::transform(Vector3D * position){}
    void Scale::transform(Dimension3D * size){}

    void Scale::transform(Vector2D * position){}
    void Scale::transform(Dimension2D * size){}
//----


}

