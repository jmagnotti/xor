#include "Point3D.h"

namespace XOR {


/* 
 * Explicit Constructor
 */
Point3D::Point3D(float p[])
{
    _color       = new float[3];
	_position = new Vector3D(p);

    for (int i=0; i<3; i++) {
		_color[i]	    = 1.0f;
		_position[i]	= p[i];
	}
}


/* 
 * Explicit Constructor
 */
Point3D::Point3D(float p[], float c[])
{
    _color       = new float[3];

	_position = new Vector3D(p);

    for (int i=0; i<3; i++) {
		_color[i]	    = c[i];
	}
}


/*
 * Explicit Constructor
 */
Point3D::Point3D(float x, float y, float z)
{
	_position = new Vector3D(x,y,z);

    _color = new float[3];
    for (int i=0; i<3; i++)
    	_color[i] = 1.0f;
}


/*
 * Explicit Constructor 
 */
Point3D::Point3D(float x, float y, float z, float c[3])
{
	_position = new Vector3D(x,y,z);

    _color = new float[3];
	for (int i=0; i<3; i++)
		_color[i] = c[i];
}


Point3D::Point3D(Vector3D * position)
{
	_position = position;
}


/*
 * Destructor
 */
Point3D::~Point3D()
{
    delete _position;
    delete[] _color;
}

/*
 * Returns true if the points position is the same as this ones
bool Point3D::compare(Interpolable * interp)
{
    bool equal = true;

    float * other = ((Point3D*)interp)->getPosition();

    // short circuits on not equal
    for (int i=0; i<3 && equal; i++) {
        equal = _position[i] == other[i];
    }

    return equal;
}
 */


/*
 * adds the values to the position arrray
 */
void Point3D::increment(float pos[3])
{
	_position->increment(pos);
}
 

/*
 * Returns the position corresponding to the given int, where 0=X, 1=Y, 2=Z.
 * Any other value will return 0.
 */
float Point3D::get(int position)
{
	return _position->get(position);
}


/*
 * Returns the position
 */
Vector3D * Point3D::getPosition()	
{ 
    return _position;
}


/*
 * Returns the color
 */
float * Point3D::getColor()
{ 
    return _color;
}
	

/*
 * multiply by [-1, -1, -1]
 */
Point3D * Point3D::invert()
{
	return new Point3D(_position->invert());
}


/*
 * For now, I am doing color in here as well. This could get messy, but if everything is
 * treated correctly, what can go wrong? This gets compiled out when display lists are used, so no performance loss is felt.
 */
void Point3D::render(void)
{
    //cout << "render at " << getX() << " "<< getY() << " "<< getZ() << endl;

	glColor3fv(getColor());
	glVertex3fv(_position->toArray());	
}


/*
 * Sets the paint for the point
 */
void Point3D::setColor(float c[3])
{	
	for (int i=0; i<3; i++)
		_color[i] = c[i];
}


/*
 * Updates the position array
 */
void Point3D::setPosition(float position[3])
{
	_position->setPosition(position);
}

/*
 * Updates the position array
 */
void Point3D::setPosition(Vector3D * position)
{
	_position->clone(position);
}


/*
 * Printing
 */
char * Point3D::toString()
{
    char * buffer = new char[60];
	sprintf(buffer, "%f %f %f\tr: %f g: %f b: %f", _position->getX(),
			_position->getY(), _position->getZ(), _color[0], _color[1],
			_color[2] );   

    return buffer;
}

}

