#include "Positionable.h"

namespace XOR {

/*
 * Must be declared in the header file so they can be used in a switch. see
 * the discussion in Paint.h
 * 
 * const int Positionable::THETA = 0;
 * const int Positionable::PHI   = 1;
 * const int Positionable::ROLL  = 2;
 */


/*
 * Default constructor
 */
Positionable::Positionable()
{
	_position   = new Translate(0.0f, 0.0f, 0.0f);
	_focalPoint = new Translate(0.0f, 0.0f, 1.0f);

	_phi        = new Rotate(0.0f, 1, 0, 0);
	_theta      = new Rotate(0.0f, 0, 1, 0);
	_roll       = new Rotate(0.0f, 0, 0, 1);

    // the default scale is 1,1,1
    _scale       = new Scale();

	_focalDistance = 1.0f;
}


/*
 * Destructor
 */
Positionable::~Positionable()
{
	delete _position;
	delete _focalPoint;

	delete _theta;
	delete _phi;
	delete _roll;

    delete _scale;
}


/*
 * Clone the other obj's values, no referencing
 */
void Positionable::clone(Positionable * other)
{
    _position->clone(other->_position);
    _focalPoint->clone(other->_focalPoint);

    _theta->clone(other->_theta);
    _phi->clone(other->_phi);
    _roll->clone(other->_roll);

    _scale->clone(other->_scale);
    _focalDistance = other->_focalDistance;
}


/*
 * pushes all subtransforms
 */
void Positionable::push()
{
    _scale->push();

	// order is important: roll, phi, theta
	_roll->push();
	_phi->push();
	_theta->push();

	_position->push();
}


/*
 * pushes reverse of all subtransforms
 * handles _scale with bool
 */
void Positionable::pushInverse(bool invertScale)
{
    if (invertScale)
        _scale->pushInverse();
    else
        _scale->push();

	// order is important: roll, phi, theta
	_roll->pushInverse();
	_phi->pushInverse();
	_theta->pushInverse();

	_position->pushInverse();
}


/*
 * pops all subtransforms
 */
void Positionable::pop()
{
    _scale->pop();
	_position->pop();

	// reverse of push
	_theta->pop();
	_phi->pop();
	_roll->pop();
}


/* 
 * increment the position values
 */
void Positionable::setTranslation(Dimension3D * position, InterpolationEngine * interpolation)
{
    cout << "hosing focal point" << endl;
    _position->set(position, interpolation);
}


/* 
 * increment the position values
 */
void Positionable::setTranslation(Dimension3D * position)
{
    _position->set(position);
    updateFocalPoint();
}

void Positionable::incrementScalar(Dimension3D * scalar)
{
    _scale->increment(scalar);
}

void Positionable::incrementScalar(Dimension3D * scalar, InterpolationEngine * interpolation)
{
    _scale->increment(scalar, interpolation);
}

void Positionable::setScalar(Dimension3D * scalar)
{
    _scale->set(scalar);
}

void Positionable::setScalar(Dimension3D * scalar, InterpolationEngine * interpolation)
{
    _scale->set(scalar, interpolation);
}

/* 
 * increment the position values
 */
void Positionable::incrementTranslation(Dimension3D * position, InterpolationEngine * interpolation)
{
    cout << "hosing focal point" << endl;
   _position->increment(position, interpolation); 
}


/* 
 * increment the position values
 */
void Positionable::incrementTranslation(Dimension3D * position)
{
    _position->increment(position);
    updateFocalPoint();
}


/*
 * increment the rotation value
 */
void Positionable::incrementRotation(const int dimension, float angle, InterpolationEngine *  interpolation)
{
    switch (dimension) {
        
        case Positionable::THETA:
            _theta->increment(angle, interpolation);
            break;
            
        case Positionable::PHI:
            _phi->increment(angle, interpolation);
            break;
            
        case Positionable::ROLL: 
            _roll->increment(angle, interpolation);
            break;
    }
    
    cout << "hosing focal point" << endl;
}


/*
 * increment the rotation value
 */
void Positionable::incrementRotation(const int dimension, float angle)
{
    switch (dimension) {
        
        case Positionable::THETA:
            _theta->increment(angle);
            break;
            
        case Positionable::PHI:
            _phi->increment(angle);
            break;
            
        case Positionable::ROLL: 
            _roll->increment(angle);
            break;
    }
    
    updateFocalPoint();
}

/*
 * set the rotation value
 */
void Positionable::setRotation(const int dimension, float angle, InterpolationEngine * interpolation)
{
    switch (dimension) {
        
        case Positionable::THETA:
            _theta->set(angle, interpolation);
            break;
            
        case Positionable::PHI:
            _phi->set(angle, interpolation);
            break;
            
        case Positionable::ROLL: 
            _roll->set(angle, interpolation);
            break;
    }
    
    updateFocalPoint();
}

/*
 * set the rotation value
 */
void Positionable::setRotation(const int dimension, float angle)
{
    switch (dimension) {
        
        case Positionable::THETA:
            _theta->set(angle);
            break;
            
        case Positionable::PHI:
            _phi->set(angle);
            break;
            
        case Positionable::ROLL: 
            _roll->set(angle);
            break;
    }
    
    updateFocalPoint();
}


/*
 * change focus and adjust transforms
 */
void Positionable::setFocalPoint(Dimension3D * point, InterpolationEngine * interpolation)
{
    cout << "Interpolation for the Focal Point is not yet implemented!" << endl;
    setFocalPoint(point);
}


void Positionable::setFocalPoint(Dimension3D * point)
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
float Positionable::getRotation(const int dimension)
{
	float angle = 0.0f;

	switch (dimension) {
        case Positionable::THETA:
            angle = _theta->_angle;
            break;
        case Positionable::PHI:
            angle = _phi->_angle;
            break;
        case Positionable::ROLL:
            angle = _roll->_angle;
            break;
	}
	return angle;
}


/*
 * return a clone of the focus point
 */
Dimension3D * Positionable::getFocalPoint()
{
    return new Dimension3D(_focalPoint->_xShift, _focalPoint->_yShift,
            _focalPoint->_zShift);
}


/*
 * move camera along focal vector
 */
void Positionable::walk(float distance)
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

	_position->increment(new Dimension3D(coords));
//    _position->increment(new Dimension3D(coords), _walkInterpolation);

	updateFocalPoint();
}


/*
 * transforms --> _focus
 */
void Positionable::updateFocalPoint()
{
	// theta and phi in radians
	float t =  (_theta->_angle / 180.0f * GraphicsConversionUtility::PI);
	float p = -(_phi->_angle / 180.0f * GraphicsConversionUtility::PI);

	// new focal point
    _focalPoint->_xShift = _position->_xShift - 
        (_focalDistance * cos(p) * sin(t));

    _focalPoint->_yShift = _position->_yShift - 
        (_focalDistance * sin(p));

    _focalPoint->_zShift = _position->_zShift - 
        (_focalDistance * cos(p) * cos(t));
}


/*
 * _focus --> transforms
 */
void Positionable::updateFromFocalPoint()
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
    //_phi->_angle = -(asin(y / _focalDistance)) / 
    _phi->_angle = (asin(y / _focalDistance)) / 
            GraphicsConversionUtility::PI * 180.0f;
    _theta->_angle = (atan2(x , z) / 
            GraphicsConversionUtility::PI * 180.0f) - 180.0f;
}


/*
 * return type
 */
char * Positionable::getRenderableType()
{
    return "POSITIONABLE";
}

/*
 * print member info
 */
void Positionable::printDebugInfo()
{
	float distance = sqrt(
	             pow(_focalPoint->_xShift - _position->_xShift, 2.0f) +
	             pow(_focalPoint->_yShift - _position->_yShift, 2.0f) +
				 pow(_focalPoint->_zShift - _position->_zShift, 2.0f));

	cout << endl << "Positionable Information: " << this << endl;

	cout << " focal distance=" << _focalDistance << endl;
	cout << " real distance="  << distance << endl;

	cout << " pos_x="     << _position->_xShift << 
		    " pos_y="     << _position->_yShift <<
		    " pos_z="     << _position->_zShift << endl;

	cout << " focus_x="     << _focalPoint->_xShift << 
		    " focus_y="     << _focalPoint->_yShift <<
		    " focus_z="     << _focalPoint->_zShift << endl;

	cout << " theta="   << _theta->_angle << 
		    " phi="     << _phi->_angle   <<
		    " roll="    << _roll->_angle  << endl;;
}


/*
 * reset the transforms
 */
void Positionable::clear()
{
    _phi->clear();
    _roll->clear();
    _theta->clear();

    _focalPoint->clear();
    _scale->clear();
    _position->clear();
}

}

