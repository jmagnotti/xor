#include "Orientation.h"

namespace XOR {

/**
 * default constructor - null orientation
 */
Orientation::Orientation()
{
	_position = new Translate(0.0f, 0.0f, 0.0f);
	_roll  = new Rotate(0.0f, 0, 0, 1);
	_phi   = new Rotate(0.0f, 0, 1, 0);
	_theta = new Rotate(0.0f, 1, 0, 0);
	_deleteOnDispose = true;
}


/*
 * clean up object
 */
Orientation::~Orientation()
{
	if (_deleteOnDispose) {
		delete _position;
		delete _roll;
		delete _phi;
		delete _theta;
	}
}


/*
 * new orientation based on existing transforms
 */
Orientation::Orientation(Translate * pos, Rotate * roll, Rotate * phi, Rotate * theta)
{
	_position = pos;
	_roll = roll;
	_phi = phi;
	_theta = theta;
	_deleteOnDispose = false;
}


/*
 * new orientation based on an existing orientation
 */
Orientation::Orientation(Orientation * baseOrientation)
{
	clone(baseOrientation);
}


/*
 * new orientation based on a transformable object
 */
Orientation::Orientation(Transformable *baseObject)
{
	_position = new Translate(baseObject->getTranslation());
	_roll  = new Rotate(baseObject->getRotation(Transformable::ROLL), 0,0,1);
	_phi   = new Rotate(baseObject->getRotation(Transformable::PHI),  0,1,0);
	_theta = new Rotate(baseObject->getRotation(Transformable::THETA),1,0,0);
	_deleteOnDispose = true;
}


/*
 * clone the other's tranforms
 */
void Orientation::clone(Orientation * other)
{
	_position->clone(other->_position);
	_roll->clone(other->_roll);
	_phi->clone(other->_phi);
	_theta->clone(other->_theta);
}


/*
 * pushes all subtransforms
 */
void Orientation::push()
{
	_position->push();
	_roll->push();
	_phi->push();
	_theta->push();
}


/*
 * pushes the inverse of all subtransforms
 */
void Orientation::pushInverse()
{
	_theta->push();
	_phi->push();
	_roll->push();
	_position->push();
}


/*
 * pops all subtransforms
 */
void Orientation::pop()
{
	_theta->pop();
	_phi->pop();
	_roll->pop();
	_position->pop();
}


Translate * Orientation::getTranslation()
{
	return _position;
}

Rotate * Orientation::getRotation(const int axis)
{
	switch (axis) {

        case Transformable::THETA:
			return _theta;
			break;
            
        case Transformable::PHI:
			return _phi;
            break;
            
        case Transformable::ROLL: 
			return _roll;
            break;
    }

}

/*
 * increment the rotation value
 */
void Orientation::incrementRotation(const int axis, float angle, InterpolationEngine *  interpolation)
{
    switch (axis) {

        case Transformable::THETA:
            _theta->increment(angle, interpolation);
            break;
            
        case Transformable::PHI:
            _phi->increment(angle, interpolation);
            break;
            
        case Transformable::ROLL: 
            _roll->increment(angle, interpolation);
            break;
    }
}


/*
 * set the rotation value
 */
void Orientation::setRotation(const int axis, float angle, InterpolationEngine * interpolation)
{
    switch (axis) {

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
}


/* 
 * increment the position values
 */
void Orientation::incrementTranslation(Vector3D * position, InterpolationEngine * interpolation)
{
   _position->increment(position, interpolation); 
}


/* 
 * set the position values
 */
void Orientation::setTranslation(Vector3D * position, InterpolationEngine * interpolation)
{
    _position->set(position, interpolation);
}


/*
 * apply this orientation to a Transformable object
 */
void Orientation::incrementTransformable(Transformable *target, InterpolationEngine * interpolation[4])
{
	target->incrementTranslation(_position->toVector(), interpolation[0]);
	target->incrementRotation(Transformable::ROLL, _roll->getAngle(), interpolation[1]);
	target->incrementRotation(Transformable::PHI, _phi->getAngle(), interpolation[2]);
	target->incrementRotation(Transformable::THETA, _theta->getAngle(), interpolation[3]);
}


/*
 * apply this orientation to a Transformable object
 */
void Orientation::setTransformable(Transformable *target, InterpolationEngine * interpolation[4])
{
	cout << _position->toVector()->toString() << endl;
	target->setTranslation(_position->toVector(), interpolation[0]);
	target->setRotation(Transformable::ROLL, _roll->getAngle(), interpolation[1]);
	target->setRotation(Transformable::PHI, _phi->getAngle(), interpolation[2]);
	target->setRotation(Transformable::THETA, _theta->getAngle(), interpolation[3]);
}


/*
 * reset the transforms
 */
void Orientation::clear()
{
    _phi->clear();
    _roll->clear();
    _theta->clear();
    _position->clear();
}


}

