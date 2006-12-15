#include "Orientate.h"

namespace XOR {

/*
 * Default constructor
 */
Orientate::Orientate()
{
	_position   = new Translate(0,0,0);
	_focalPoint = new Translate(0,0,1);
	_phi        = new Rotate(0, 1,0,0);
	_theta      = new Rotate(0, 0,1,0);
	_roll       = new Rotate(0, 0,0,1);

	_focalDistance = 1.0f;
}


/*
 * Explicit constructors
 */
Orientate::Orientate(Translate * position, float theta, float phi, float roll)
{
	_position   = position;
	_focalPoint = new Translate(0,0,0);
	_phi        = new Rotate(phi,   1,0,0);
	_theta      = new Rotate(theta, 0,1,0);
	_roll       = new Rotate(roll,  0,0,1);

	_focalDistance = 1.0f;

	updateFocalPoint();
}


/*
 * Explicit Constructor
 */
Orientate::Orientate(Translate * position, Translate * focalPoint)
{
	_position   = position;
	_focalPoint = focalPoint;

	_phi   = new Rotate(0, 1,0,0);
	_theta = new Rotate(0, 0,1,0);
	_roll  = new Rotate(0, 0,0,1);

	float _focalDistance = sqrt(
	             pow(_focalPoint->_xShift - _position->_xShift, 2.0f) +
	             pow(_focalPoint->_yShift - _position->_yShift, 2.0f) +
				 pow(_focalPoint->_zShift - _position->_zShift, 2.0f));
 
	updateFromFocalPoint();
}


/*
 * Destructor
 */
Orientate::~Orientate()
{
	delete _position;
	delete _focalPoint;
	delete _theta;
	delete _phi;
	delete _roll;
}


/*
 * Clone copier
 */
void Orientate::clone(Orientate * other)
{
    _position->clone(other->_position);
    _focalPoint->clone(other->_focalPoint);

    _theta->clone(other->_theta);
    _phi->clone(other->_phi);
    _roll->clone(other->_roll);

    _focalDistance = other->_focalDistance;
}


/*
 * pushes all subtransforms
 */
void Orientate::push()
{
	// order is important: roll, phi, theta
	_roll->push();
	_phi->push();
	_theta->push();

	_position->push();
}


/*
 * pushes reverse of all subtransforms
 */
void Orientate::pushInverse()
{
	// order is important: roll, phi, theta
	_roll->pushInverse();
	_phi->pushInverse();
	_theta->pushInverse();

	_position->pushInverse();
}


/*
 * pops all subtransforms
 */
void Orientate::pop()
{
	_position->pop();

	// reverse of push: theta, phi, roll
	_theta->pop();
	_phi->pop();
	_roll->pop();
}


/* 
 * increment the position values
 */
void Orientate::incrementPosition(Point3D * point)
{
	_position->increment(point);
	updateFocalPoint();
}


/*
 * increment the rotation value
 */
void Orientate::incrementRotation(int dimension, float angle)
{
	switch (dimension) {
        case 0: // theta
            _theta->_angle += angle;
            break;
        case 1: // phi
            _phi->_angle += angle;
            break;
        case 2: // roll
            _roll->_angle += angle;
            break;
	}
	updateFocalPoint();
}


/*
 * change focus and adjust transforms
 */
void Orientate::setFocalPoint(Point3D *point)
{
	printDebugInfo();
	_focalPoint->_xShift = point->getX();
	_focalPoint->_yShift = point->getY();
	_focalPoint->_zShift = point->getZ();

	_focalDistance = sqrt(
	             pow(_focalPoint->_xShift - _position->_xShift, 2.0f) +
	             pow(_focalPoint->_yShift - _position->_yShift, 2.0f) +
				 pow(_focalPoint->_zShift - _position->_zShift, 2.0f));

	updateFromFocalPoint();
	printDebugInfo();
}


/*
 * return the rotation value
 */
float Orientate::getRotation(int dimension)
{
	float angle = 0.0;
	switch (dimension) {
        case 0: // theta
            angle = _theta->_angle;
            break;
        case 1: // phi
            angle = _phi->_angle;
            break;
        case 2: // roll
            angle = _roll->_angle;
            break;
	}
	return angle;
}


/*
 * return a copy of the focus point
 */
Point3D * Orientate::getFocalPoint()
{
	return new Point3D(_focalPoint->_xShift, _focalPoint->_yShift, _focalPoint->_zShift);
}


/*
 * move camera along focal vector
 */
void Orientate::walk(float distance)
{
	updateFocalPoint();

	// calculate new position
	float coords[3];
	coords[0] = (_focalPoint->_xShift - _position->_xShift) * distance;
	coords[1] = (_focalPoint->_yShift - _position->_yShift) * distance;
	coords[2] = (_focalPoint->_zShift - _position->_zShift) * distance;
	/*float t =  (_theta->_angle / 180.0f * GraphicsConversionUtility::PI);
	float p = -(_phi->_angle / 180.0f * GraphicsConversionUtility::PI);
	coords[0] = (distance * cos(p) * sin(t));
	coords[1] = (distance * sin(p));
	coords[2] = (distance * cos(p) * cos(t));*/
	_position->increment(new Point3D(coords));

	updateFocalPoint();
}


/*
 * transforms --> _focus
 */
void Orientate::updateFocalPoint()
{
	// theta and phi in radians
	float t =  (_theta->_angle / 180.0f * GraphicsConversionUtility::PI);
	float p = -(_phi->_angle / 180.0f * GraphicsConversionUtility::PI);

	// new focal point
	_focalPoint->_xShift = _position->_xShift - (_focalDistance * cos(p) * sin(t));
	_focalPoint->_yShift = _position->_yShift - (_focalDistance * sin(p));
	_focalPoint->_zShift = _position->_zShift - (_focalDistance * cos(p) * cos(t));
}


/*
 * _focus --> transforms
 */
void Orientate::updateFromFocalPoint()
{
	// the camera can be rotated to the given focal point in
	// only two axes of rotations: theta and phi (not roll)
	// current behavior is to preserve roll upon focus reset
	// uncomment the following line to reset roll upon reset
	//_roll = 0.0;

	// focal vector relative to position
	float x = _focalPoint->_xShift - _position->_xShift;
	float y = _focalPoint->_yShift - _position->_yShift;
	float z = _focalPoint->_zShift - _position->_zShift;

	// new rotation
	_phi->_angle = -(asin(y / _focalDistance)) / GraphicsConversionUtility::PI * 180.0f;
	_theta->_angle = (atan2(x , z) / GraphicsConversionUtility::PI * 180.0f) - 180.0f;
}


/*
 * print member info
 */
void Orientate::printDebugInfo()
{
	float distance = sqrt(
	             pow(_focalPoint->_xShift - _position->_xShift, 2.0f) +
	             pow(_focalPoint->_yShift - _position->_yShift, 2.0f) +
				 pow(_focalPoint->_zShift - _position->_zShift, 2.0f));

	cout << endl;

	cout << " focal distance=" << _focalDistance << endl;
	cout << " real distance="  << distance << endl;

	cout << " p_x="     << _position->_xShift << 
		    " p_y="     << _position->_yShift <<
		    " p_z="     << _position->_zShift << endl;

	cout << " f_x="     << _focalPoint->_xShift << 
		    " f_y="     << _focalPoint->_yShift <<
		    " f_z="     << _focalPoint->_zShift << endl;

	cout << " theta="   << _theta->_angle << 
		    " phi="     << _phi->_angle <<
		    " roll="    << _roll->_angle << endl;;
}

}

