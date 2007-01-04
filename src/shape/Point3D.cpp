#include "Point3D.h"

namespace XOR {

/*
 * Default Constructor
 */
Point3D::Point3D()
{
    _color       = new float[3];
    _position    = new float[3];

	for(int i=0; i<3; i++) {
		_color[i]       = 1.0f;
		_position[i]    = 0.0f;
	}
}


/* 
 * Explicit Constructor
 */
Point3D::Point3D(float p[])
{
    _color       = new float[3];
    _position    = new float[3];

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
    _position    = new float[3];

    for (int i=0; i<3; i++) {
		_color[i]	    = c[i];
		_position[i]	= p[i];
	}
}


/*
 * Explicit Constructor
 */
Point3D::Point3D(float x, float y, float z)
{
    _position    = new float[3];
    _position[0] = x;
	_position[1] = y;
	_position[2] = z;

    _color = new float[3];
    for (int i=0; i<3; i++)
    	_color[i] = 1.0f;
}


/*
 * Explicit Constructor 
 */
Point3D::Point3D(float x, float y, float z, float c[3])
{
    _position       = new float[3];
    _position[0]	= x;
	_position[1]	= y;		
	_position[2]	= z;		

    _color = new float[3];
	for (int i=0; i<3; i++)
		_color[i] = c[i];
}


/*
 * Destructor
 */
Point3D::~Point3D()
{
    delete[] _position;
    delete[] _color;
}


/*
 * Sets the position to the given position
 */
void Point3D::clonePosition(Point3D * p)
{
    setPosition(p->getPosition());
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
    for (int i=0; i<3; i++)
        _position[i] += pos[i];
}
 

/*
 * Returns the position corresponding to the given int, where 0=X, 1=Y, 2=Z.
 * Any other value will return 0.
 */
float Point3D::get(int position)
{
    if (position >= 0 && position <= 2)
        return _position[position];
    else
        return 0;
}


/*
 * Returns the X position
 */
float Point3D::getX()
{ 
    return _position[0];	
}


/*
 * Returns the Y position
 */
float Point3D::getY()			
{ 
    return _position[1];
}


/*
 * Returns the Z position
 */
float Point3D::getZ()
{ 
    return _position[2];	
}


/*
 * Returns the position
 */
float * Point3D::getPosition()	
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
	return new Point3D( - _position[0],
						- _position[1],
						- _position[2] );
}


/*
 * addition
 */
Point3D * Point3D::operator +(Point3D * point)
{
	return new Point3D( getX() + point->getX(),
                        getY() + point->getY(),
                        getZ() + point->getZ()  );
}


/*
 * subtraction
 */
Point3D * Point3D::operator -(Point3D * point)
{
	return new Point3D( getX() - point->getX(),
	                    getY() - point->getY(),
	                    getZ() - point->getZ()  );
}


/*
 * For now, I am doing color in here as well. This could get messy, but if everything is
 * treated correctly, what can go wrong? This gets compiled out when display lists are used, so no performance loss is felt.
 */
void Point3D::render(void)
{
    //cout << "render at " << getX() << " "<< getY() << " "<< getZ() << endl;

	glColor3fv(getColor());
	glVertex3fv(getPosition());	
    //glVertex3f(getX(), getY(), getZ());
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
 * Scales each point by the specified amount
void Point3D::scale(float scaleAmount)
{
   for (int i=0; i<3; i++)
       _position[i] *= scaleAmount;
}
 */

/*
 * Updates the position array
 */
void Point3D::setPosition(float pos[])
{
    for (int i=0; i<3; i++)
        _position[i] = pos[i];
}

/*
 * Printing
 */
char * Point3D::toString()
{
    char * buffer = new char[60];
    sprintf(buffer, "%f %f %f\tr: %f g: %f b: %f", getX(), getY(), getZ(), _color[0], _color[1], _color[2] );   

    return buffer;
}

}

