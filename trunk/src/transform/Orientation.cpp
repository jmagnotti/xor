#include "Orientation.h"

namespace XOR {

/*
 * Must be declared in the header file so they can be used in a switch. see
 * the discussion in Paint.h
 * 
 * const int Orientation::THETA = 0;
 * const int Orientation::PHI   = 1;
 * const int Orientation::ROLL  = 2;
 */ 

/**
 * default constructor - null orientation
 */
Orientation::Orientation()
{
	_position   = Translate::CreateTranslate(0.0f, 0.0f, 0.0f);
	_focalPoint = new Vector3D(0.0f, 0.0f, 1.0f);

	_phi        = new Rotate(0.0f, 1, 0, 0);
	_theta      = new Rotate(0.0f, 0, 1, 0);
	_roll       = new Rotate(0.0f, 0, 0, 1);

	_focalDistance = 1.0f;
}


/*
 * clean up object
 */
Orientation::~Orientation()
{
	delete _position;
	delete _focalPoint;

	delete _theta;
	delete _phi;
	delete _roll;
}


/*
 * new orientation based on existing transforms
 */
Orientation::Orientation(Translate * position, Rotate * roll, Rotate * phi, Rotate * theta)
{
	_position = position;
	_focalPoint = new Vector3D(0.0f, 0.0f, 1.0f);
	_roll = roll;
	_phi = phi;
	_theta = theta;
	updateFocalPoint();
}


/*
 * new orientation based on existing transforms
 */
Orientation::Orientation(Translate * position, Vector3D * focalPoint)
{
	_position = position;
	_focalPoint = focalPoint;
	_phi        = new Rotate(0.0f, 1, 0, 0);
	_theta      = new Rotate(0.0f, 0, 1, 0);
	_roll       = new Rotate(0.0f, 0, 0, 1);
	updateFromFocalPoint();
}


/*
 * clone the other's tranforms
 */
void Orientation::clone(Orientation * other)
{
    _position->clone(other->_position);
    _focalPoint->clone(other->_focalPoint);

    _theta->clone(other->_theta);
    _phi->clone(other->_phi);
    _roll->clone(other->_roll);

    _focalDistance = other->_focalDistance;
}


/*
 *
 */
Orientation * Orientation::clone()
{
    Orientation * cloned = new Orientation(_position, _roll, _phi, _theta);
    cloned->_focalPoint = _focalPoint->clone();

    return cloned;
}


/*
 * pushes all subtransforms
 */
void Orientation::push()
{
	_position->push();

	// order is important: roll, phi, theta
	_roll->push();
	_phi->push();
	_theta->push();
}


/*
 * pushes reverse of all subtransforms
 * handles _scale with bool
 */
void Orientation::pushInverse()
{
	//_position->pushInverse();

	// order is important: roll, phi, theta
	_roll->pushInverse();
	_phi->pushInverse();
	_theta->pushInverse();

	_position->pushInverse();
}


/*
 * pops all subtransforms
 */
void Orientation::pop()
{
	// reverse of push
	_theta->pop();
	_phi->pop();
	_roll->pop();

	_position->pop();
}


/*
 *
 */
void Orientation::moveAlongFocalVector(float distance)
{
	updateFocalPoint();

	// calculate new position by obtaining focus vector and multiplying
	// by the desired distance
	float coords[3];
	coords[0] = (_focalPoint->get(0) - _position->_translation[0]) * distance;
	coords[1] = (_focalPoint->get(1) - _position->_translation[1]) * distance;
	coords[2] = (_focalPoint->get(2) - _position->_translation[2]) * distance;

    for (int i=0; i<3; i++)
        coords[i] = (_focalPoint->get(i) - _position->_translation[i]) * distance;

	//_position->increment(new Vector3D(coords), interpolation);

	updateFocalPoint();
}


/*
 * transforms --> _focus
 */
void Orientation::updateFocalPoint()
{
    //cout << "Updating the focal point" << endl;

	// theta and phi in radians
    /*
	float t =  (_theta->_angle / 180.0f * GraphicsConversionUtility::PI);
	float p = -(_phi->_angle / 180.0f * GraphicsConversionUtility::PI);

	// new focal point
    _focalPoint->_translation[0] = _position->_translation[0] - 
        (_focalDistance * cos(p) * sin(t));

    _focalPoint->_translation[1] = _position->_translation[1] - 
        (_focalDistance * sin(p));

    _focalPoint->_translation[2] = _position->_translation[2] - (_focalDistance * cos(p) * cos(t));
    */
}


/*
 * _focus --> transforms
 */
void Orientation::updateFromFocalPoint()
{
	// the camera can be rotated to the given focal point in
	// only two axes of rotations: theta and phi (not roll)
	// current behavior is to preserve roll upon focus reset
	// uncomment the following line to reset roll upon reset
	//_roll = 0.0;

	// focal vector relative to position
	float x = _focalPoint->getX() - _position->_translation[0];
	float y = _focalPoint->getY() - _position->_translation[1];
	float z = _focalPoint->getZ() - _position->_translation[2];

	// new rotation
    _phi->_angle = (asin(y / _focalDistance)) / 
            GraphicsConversionUtility::PI * 180.0f;
    _theta->_angle = (atan2(x , z) / 
            GraphicsConversionUtility::PI * 180.0f) - 180.0f;
}


/*
 * print member info
 */
void Orientation::print()
{
    return ;
    /*
	float distance = sqrt(
	             pow(_focalPoint->_translation[0] - _position->_translation[0], 2.0f) +
	             pow(_focalPoint->_translation[1] - _position->_translation[1], 2.0f) +
				 pow(_focalPoint->_translation[2] - _position->_translation[2], 2.0f));

	cout << endl << "---Transformable Information " << this << " ---" << endl;

	cout << "focal distance=" << _focalDistance << endl;
	cout << "real distance="  << distance << endl;

	cout << "pos_x="     << _position->_translation[0] << 
		    "pos_y="     << _position->_translation[2] <<
		    "pos_z="     << _position->_translation[2] << endl;

	cout << "focus_x="     << _focalPoint->_translation[0] << 
		    "focus_y="     << _focalPoint->_translation[1] <<
		    "focus_z="     << _focalPoint->_translation[2] << endl;

	cout << "theta="   << _theta->_angle << 
		    "phi="     << _phi->_angle   <<
		    "roll="    << _roll->_angle  << endl;;
*/
}

/*
 * reset the transforms
 */
void Orientation::toIdentity()
{
    _phi->toIdentity();
    _roll->toIdentity();
    _theta->toIdentity();

    _position->toIdentity();
}

void Orientation::transform(Vector2D * position){}
void Orientation::transform(Dimension2D * size){}

void Orientation::transform(Vector3D * position){}
void Orientation::transform(Dimension3D * size){}

}

