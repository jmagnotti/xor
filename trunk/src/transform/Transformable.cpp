#include "Transformable.h"


namespace XOR {

/*
 * Must be declared in the header file so they can be used in a switch. see
 * the discussion in Paint.h
 * 
 * const int Transformable::THETA = 0;
 * const int Transformable::PHI   = 1;
 * const int Transformable::ROLL  = 2;
 */ 
/*
 * Default constructor
 */
Transformable::Transformable()
{
	_position   = new Translate();
	_focalPoint = new Translate(0.0f, 0.0f, 1.0f);

	_phi        = new Rotate(0.0f, 1, 0, 0);
	_theta      = new Rotate(0.0f, 0, 1, 0);
	_roll       = new Rotate(0.0f, 0, 0, 1);

    _scale      = new Scale();
    _stretch    = new Stretch();

	_focalDistance = 1.0f;
	_transformed = false;
}


/*
 * Destructor
 */
Transformable::~Transformable()
{
	delete _position;
	delete _focalPoint;

	delete _theta;
	delete _phi;
	delete _roll;

    delete _scale;
    delete _stretch;
}


/*
 * Clone the other obj's values, no referencing
 */
void Transformable::clone(Transformable * other)
{
    _position->clone(other->_position);
    _focalPoint->clone(other->_focalPoint);

    _theta->clone(other->_theta);
    _phi->clone(other->_phi);
    _roll->clone(other->_roll);

    _scale->clone(other->_scale);
    _focalDistance = other->_focalDistance;

	_transformed = other->_transformed;
}


/*
 * pushes all subtransforms
 */
void Transformable::push()
{
	_stretch->push();

    _scale->push();

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
void Transformable::pushInverse(bool invertScale)
{
    if (invertScale)
        _scale->pushInverse();
    else
        _scale->push();

	_position->pushInverse();

	// order is important: roll, phi, theta
	_roll->pushInverse();
	_phi->pushInverse();
	_theta->pushInverse();

}


/*
 * pops all subtransforms
 */
void Transformable::pop()
{
	// reverse of push
	_theta->pop();
	_phi->pop();
	_roll->pop();

	_position->pop();

    _scale->pop();

    _stretch->pop();
}


/*
 * return the translation as a vector
 */
Vector3D * Transformable::getTranslation()
{
	return _position->toVector();
}

/* 
 * increment the position values
 */
void Transformable::incrementTranslation(Vector3D * position, InterpolationEngine * interpolation)
{
	_transformed = true;
   _position->increment(position, interpolation); 
}


/* 
 * increment the position values
 */
void Transformable::incrementTranslation(Vector3D * position)
{
	_transformed = true;
    _position->increment(position);
    updateFocalPoint();
}


/* 
 * set the position values
 */
void Transformable::setTranslation(Vector3D * position, InterpolationEngine * interpolation)
{
	_transformed = true;
    _position->set(position, interpolation);
}


/* 
 * set the position values
 */
void Transformable::setTranslation(Vector3D * position)
{
	_transformed = true;
    _position->set(position);
    updateFocalPoint();
}


void Transformable::incrementScalar(Vector3D * scalar)
{
	_transformed = true;
    _scale->increment(scalar);
}


void Transformable::incrementScalar(Vector3D * scalar, InterpolationEngine * interpolation)
{
	_transformed = true;
    _scale->increment(scalar, interpolation);
}


void Transformable::setScalar(Vector3D * scalar)
{
	_transformed = true;
    _scale->set(scalar);
}


void Transformable::setScalar(Vector3D * scalar, InterpolationEngine * interpolation)
{
	_transformed = true;
    _scale->set(scalar, interpolation);
}


Vector3D * Transformable::getStrech()
{
	return _stretch->toVector();
}


void Transformable::setStretch(Vector3D * stretch, InterpolationEngine * interpolation) 
{
	_stretch->setOrigin(getBaseVector());

	_transformed = true;
	_stretch->set(stretch, interpolation);
}

void Transformable::setStretch(Vector3D * stretch)
{
	_stretch->setOrigin(getBaseVector());

	_transformed = true;
	_stretch->set(stretch);
}

void Transformable::incrementStretch(Vector3D * stretch, InterpolationEngine * interpolation) 
{
	_stretch->setOrigin(getBaseVector());

	_transformed = true;
	_stretch->increment(stretch, interpolation);
}

void Transformable::incrementStretch(Vector3D * stretch)
{
	_stretch->setOrigin(getBaseVector());

	_transformed = true;
	_stretch->increment(stretch);
}


/*
 * increment the rotation value
 */
void Transformable::incrementRotation(const int dimension, float angle, InterpolationEngine *  interpolation)
{
	_transformed = true;
    switch (dimension) {
        
        case Transformable::THETA:
            _theta->increment(angle, interpolation);
            break;
            
        case Transformable::PHI:
            _phi->increment(angle, interpolation);
            break;
            
        case Transformable::ROLL: 
			//cout << "ang: " << angle << endl;
            _roll->increment(angle, interpolation);
            break;
    }
    
    //cout << "hosing focal point" << endl;
}


/*
 * increment the rotation value
 */
void Transformable::incrementRotation(const int dimension, float angle)
{
	_transformed = true;
    switch (dimension) {
        
        case Transformable::THETA:
            _theta->increment(angle);
            break;
            
        case Transformable::PHI:
            _phi->increment(angle);
            break;
            
        case Transformable::ROLL: 
            _roll->increment(angle);
            break;
    }
    
    updateFocalPoint();
}


/*
 * set the rotation value
 */
void Transformable::setRotation(const int dimension, float angle, InterpolationEngine * interpolation)
{
	_transformed = true;
    switch (dimension) {
        
        case Transformable::THETA:
            _theta->set(angle, interpolation);
            break;
            
        case Transformable::PHI:
            _phi->set(angle, interpolation);
            break;
            
        case Transformable::ROLL: 
            _roll->set(angle, interpolation);
            break;
    }
    
    updateFocalPoint();
}


/*
 * set the rotation value
 */
void Transformable::setRotation(const int dimension, float angle)
{
	_transformed = true;
    switch (dimension) {
        
        case Transformable::THETA:
            _theta->set(angle);
            break;
            
        case Transformable::PHI:
            _phi->set(angle);
            break;
            
        case Transformable::ROLL: 
            _roll->set(angle);
            break;
    }
    
    updateFocalPoint();
}


/*
 * change focus and adjust transforms
 */
void Transformable::setFocalPoint(Vector3D * point, InterpolationEngine * interpolation)
{
	_transformed = true;
	_focalPoint->_xShift = point->getX();
	_focalPoint->_yShift = point->getY();
	_focalPoint->_zShift = point->getZ();

	_focalDistance = sqrt(
	             pow(_focalPoint->_xShift - _position->_xShift, 2.0f) +
	             pow(_focalPoint->_yShift - _position->_yShift, 2.0f) +
				 pow(_focalPoint->_zShift - _position->_zShift, 2.0f));

    updateFromFocalPoint(interpolation);
}

void Transformable::incrementFocalPoint(Vector3D * point, InterpolationEngine * interpolation)
{
    _transformed = true;

	_focalPoint->_xShift += point->getX();
	_focalPoint->_yShift += point->getY();
	_focalPoint->_zShift += point->getZ();

	_focalDistance = sqrt(
	             pow(_focalPoint->_xShift - _position->_xShift, 2.0f) +
	             pow(_focalPoint->_yShift - _position->_yShift, 2.0f) +
				 pow(_focalPoint->_zShift - _position->_zShift, 2.0f));

    updateFromFocalPoint(interpolation);
}

void Transformable::incrementFocalPoint(Vector3D * point)
{
	_focalPoint->_xShift += point->getX();
	_focalPoint->_yShift += point->getY();
	_focalPoint->_zShift += point->getZ();

	_focalDistance = sqrt(
	             pow(_focalPoint->_xShift - _position->_xShift, 2.0f) +
	             pow(_focalPoint->_yShift - _position->_yShift, 2.0f) +
				 pow(_focalPoint->_zShift - _position->_zShift, 2.0f));

    updateFromFocalPoint();
}

/*
 * set fp
 */
void Transformable::setFocalPoint(Vector3D * point)
{
	_transformed = true;
    cout << "setting focal point from Vec3D" << endl;
	print();

	_focalPoint->_xShift = point->getX();
	_focalPoint->_yShift = point->getY();
	_focalPoint->_zShift = point->getZ();

	_focalDistance = sqrt(
	             pow(_focalPoint->_xShift - _position->_xShift, 2.0f) +
	             pow(_focalPoint->_yShift - _position->_yShift, 2.0f) +
				 pow(_focalPoint->_zShift - _position->_zShift, 2.0f));

	updateFromFocalPoint();
	print();
}


/*
 * return the rotation value
 */
float Transformable::getRotation(const int dimension)
{
	float angle = 0.0f;

	switch (dimension) {
        case Transformable::THETA:
            angle = _theta->_angle;
            break;
        case Transformable::PHI:
            angle = _phi->_angle;
            break;
        case Transformable::ROLL:
            angle = _roll->_angle;
            break;
	}
	return angle;
}


/*
 * return a clone of the focus point
 */
Vector3D * Transformable::getFocalPoint()
{
    return new Vector3D(_focalPoint->_xShift, _focalPoint->_yShift,
            _focalPoint->_zShift);
}


/*
 * move camera along focal vector
 */
void Transformable::walk(float distance, InterpolationEngine * interpolation)
{
	_transformed = true;
	updateFocalPoint();

	// calculate new position by obtaining focus vector and multiplying
	// by the desired distance
	float coords[3];
	coords[0] = (_focalPoint->_xShift - _position->_xShift) * distance;
	coords[1] = (_focalPoint->_yShift - _position->_yShift) * distance;
	coords[2] = (_focalPoint->_zShift - _position->_zShift) * distance;

	_position->increment(new Vector3D(coords), interpolation);

	updateFocalPoint();
}


/*
 * transforms --> _focus
 */
void Transformable::updateFocalPoint()
{
    cout << "Updating the focal point" << endl;

	// theta and phi in radians
	float t =  (_theta->_angle / 180.0f * GraphicsConversionUtility::PI);
	float p = -(_phi->_angle / 180.0f * GraphicsConversionUtility::PI);

	// new focal point
    _focalPoint->_xShift = _position->_xShift - 
        (_focalDistance * cos(p) * sin(t));

    _focalPoint->_yShift = _position->_yShift - 
        (_focalDistance * sin(p));

    _focalPoint->_zShift = _position->_zShift - (_focalDistance * cos(p) * cos(t));
}


/*
 * _focus --> transforms
 */
void Transformable::updateFromFocalPoint()
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
    _phi->_angle = (asin(y / _focalDistance)) / 
            GraphicsConversionUtility::PI * 180.0f;
    _theta->_angle = (atan2(x , z) / 
            GraphicsConversionUtility::PI * 180.0f) - 180.0f;
}


/*
 * update with interp
 */
void Transformable::updateFromFocalPoint(InterpolationEngine * interpolation)
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
    _phi->set((asin (y / _focalDistance)) / GraphicsConversionUtility::PI * 180.0f, interpolation);
    _theta->set((atan2(x , z) / GraphicsConversionUtility::PI * 180.0f) - 180.0f, interpolation);
            
    //_angle = (asin(y / _focalDistance)) / GraphicsConversionUtility::PI * 180.0f;
    //_angle = (atan2(x , z) / GraphicsConversionUtility::PI * 180.0f) - 180.0f;
}


/*
 * print member info
 */
void Transformable::print()
{
	float distance = sqrt(
	             pow(_focalPoint->_xShift - _position->_xShift, 2.0f) +
	             pow(_focalPoint->_yShift - _position->_yShift, 2.0f) +
				 pow(_focalPoint->_zShift - _position->_zShift, 2.0f));

	cout << endl << "---Transformable Information " << this << " ---" << endl;

	cout << "focal distance=" << _focalDistance << endl;
	cout << "real distance="  << distance << endl;

	cout << "pos_x="     << _position->_xShift << 
		    "pos_y="     << _position->_yShift <<
		    "pos_z="     << _position->_zShift << endl;

	cout << "focus_x="     << _focalPoint->_xShift << 
		    "focus_y="     << _focalPoint->_yShift <<
		    "focus_z="     << _focalPoint->_zShift << endl;

	cout << "theta="   << _theta->_angle << 
		    "phi="     << _phi->_angle   <<
		    "roll="    << _roll->_angle  << endl;;

	cout << "scale_x="   << _scale->_xScale << 
		    "scale_y="   << _scale->_xScale   <<
		    "scale_z="   << _scale->_xScale  << endl;;
}


/*
 * reset the transforms
 */
void Transformable::clear()
{
    _phi->clear();
    _roll->clear();
    _theta->clear();

    _focalPoint->clear();
    _scale->clear();
    _position->clear();

	_transformed = false;
}


/*
 * true if any Transforms have been modified
 */
bool Transformable::isTransformed()
{
	return _transformed;
}

}

