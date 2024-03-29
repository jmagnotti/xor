#include "Vector3D.h"


namespace XOR {

const int Vector3D::X = 0;
const int Vector3D::Y = 1;
const int Vector3D::Z = 2;

/*
 * Min function
 */
Vector3D * Vector3D::Min(Vector3D * a, Vector3D * b)
{
    float min[3];

    for (int i=0; i<3; i++)
        min[i] = a->get(i) < b->get(i) ? a->get(i) : b->get(i);
        
    return new Vector3D(min);
}


/*
 * Max function
 */
Vector3D * Vector3D::Max(Vector3D * a, Vector3D * b)
{
    float max[3];

    for (int i=0; i<3; i++)
        max[i] = a->get(i) > b->get(i) ? a->get(i) : b->get(i);
        
    return  new Vector3D(max);
}


/*
 * Default Constructor
 */
Vector3D::Vector3D()
{
    for (int i=0; i<3; i++)
        _position[i] = 0.0f;
}


/*
 * Explicit Constructor
 */
Vector3D::Vector3D(float value)
{
    for (int i=0; i<3; i++)
        _position[i] = value;
}


/*
 * Explicit Constructor
 */
Vector3D::Vector3D(float x, float y, float z)
{
    _position[0] = x;
    _position[1] = y;
    _position[2] = z;
}


/*
 * Explicit Constructor
 */
Vector3D::Vector3D(float points[3])
{
    for (int i=0; i<3; i++)
        _position[i] = points[i];
}


/*
 * string cstr
 */
Vector3D::Vector3D(char * vals)
{
    char * result = NULL;
    char delims[] = " ";
//FIXME why not try...catch ?
    result = strtok(vals, delims); 
    _position[0] = atof(result);

    for (int i=1; i<3; i++) {
        result = strtok(NULL, delims); 
        _position[i] = atof(result);
    }
}


/*
 * Increment
 */
void Vector3D::increment(Vector3D * other)
{
    for(int i=0; i<3; i++)
        _position[i] += other->_position[i];
}


/*
 * scale
 */
void Vector3D::scale(Vector3D * other)
{
    for(int i=0; i<3; i++)
        _position[i] *= other->_position[i];
}


/*
 * complement
 */
Vector3D * Vector3D::complement()
{
    float points[3];

    for (int i=0; i<3; i++) {
        if (_position[i])
            points[i] = 0.0f;
        else
            points[i] = 1.0f;
    }

    return new Vector3D(points);
}


/*
 * abs value
 */
Vector3D * Vector3D::absoluteValue()
{
    float points[3];

    for (int i=0; i<3; i++) {
        if (_position[i] > 0.0f)
            points[i] = _position[i];
        else
            points[i] = -1 * _position[i];
    }

    return new Vector3D(points);
}


/*
 * Easy subtraction
 */
Vector3D * Vector3D::operator - (Vector3D * other)
{
    return new Vector3D( _position[0] - other->getX(), 
                         _position[1] - other->getY(),
                         _position[2] - other->getZ() );
}



/*
 * uniform subtraction
 */
Vector3D * Vector3D::operator - (float a)
{
    return new Vector3D( _position[0] - a,
                         _position[1] - a,
                         _position[2] - a);
}


/*
 * Easy addition
 */
Vector3D * Vector3D::operator + (Vector3D * other)
{
    return new Vector3D( _position[0] + other->getX(), 
                         _position[1] + other->getY(),
                         _position[2] + other->getZ() );
}


Vector3D * Vector3D::operator + (float a)
{
    return new Vector3D( _position[0] + a,
                         _position[1] + a,
                         _position[2] + a);
}


/*
 * Easy multiplication
 */
Vector3D * Vector3D::operator * (Vector3D * other)
{
    return new Vector3D( _position[0] * other->getX(), 
                         _position[1] * other->getY(),
                         _position[2] * other->getZ() );
}



/*
 * uniform multiplication
 */
Vector3D * Vector3D::operator * (float a)
{
    return new Vector3D( _position[0] * a,
                         _position[1] * a,
                         _position[2] * a);
}


/*
 * Easy division
 */
Vector3D * Vector3D::operator / (Vector3D * other)
{
    return new Vector3D( _position[0] / other->getX(), 
                         _position[1] / other->getY(),
                         _position[2] / other->getZ() );
}


Vector3D * Vector3D::operator / (float a)
{
    return new Vector3D( _position[0] / a,
                         _position[1] / a,
                         _position[2] / a);
}

/*
 * !=
 */
bool Vector3D::operator != (Vector3D * other)
{
    return ! ((*this) == other);
}


/*
 * ==
 */
bool Vector3D::operator == (Vector3D * other)
{
    bool equal = true;
    int i=0;

    while (equal && i<3) {
        equal = get(i) == other->get(i);
        ++i;;
    }

    return equal;
}

float Vector3D::get(int dimension) 
{
	if (dimension >=  Vector3D::X && dimension <= Vector3D::Z)
		return _position[dimension];
	else
		return 0;
}

float Vector3D::getX() const
{
   	return _position[0];
}

float Vector3D::getY() const
{
   	return _position[1];
}


float Vector3D::getZ() const
{
   	return _position[2];
}


/*
 * return -1*position
 */
Vector3D * Vector3D::invert()
{
	return new Vector3D(- _position[0],
						- _position[1],
						- _position[2]);
}


/*
 * pos[i]+=other[i]
 */
void Vector3D::increment(float position[3])
{
	for(int i=0; i<3; i++)
		_position[i] += position[i];
}


/*
 * sets the position of the vec
 */
void Vector3D::setPosition(float position[3])
{
	for(int i=0; i<3; i++)
		_position[i] = position[i];
}

void Vector3D::setPosition(const int position, float value)
{
	//if (position >=  Vector3D::X && position <= Vector3D::Z)
		_position[position] = value;
}

void Vector3D::incrementPosition(const int position, float increment)
{
	//if (position >=  Vector3D::X && position <= Vector3D::Z)
		_position[position] += increment;
}

/*
 * toArray
 */
float * Vector3D::toArray()
{
	return _position;
}


/*
 * copy the other Vector3D's position
 */
void Vector3D::clone(Vector3D * other)
{
	for(int i=0; i<3; i++)
		_position[i] = other->_position[i];
}


/*
 * returns a cloned instance
 */
Vector3D * Vector3D::clone()
{
    return new Vector3D(_position);
}


char * Vector3D::toString()
{
    char * buffer = new char[60];
	sprintf(buffer, "%f %f %f", getX(), getY(), getZ());

    return buffer;
}


}

