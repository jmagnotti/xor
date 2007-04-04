#include "Transformable.h"


namespace XOR {

/*
 * Default constructor
 */
Transformable::Transformable()
{
	_orientation = new Orientation();
	_scale       = new Scale();
	_stretch     = new Stretch();
}


/*
 * Destructor
 */
Transformable::~Transformable()
{
	delete _orientation;
	delete _stretch;
	delete _scale;
}


/*
 * Clone the other obj's values, no referencing
 */
void Transformable::clone(Transformable * other)
{
	_orientation->clone(other->_orientation);
	_scale->clone(other->_scale);

	// TODO: add Stretch::Clone()
	//_stretch->clone(other->_stretch);
}


/*
 *
 */
Orientation * Transformable::cloneOrientation()
{
    /*
        Orientation * newOrientation = new Orientation();
        newOrientation->clone(_orientation);
    */

	return _orientation->clone();
}


/*
 * return the dimension described by our transforms
Dimension3D * Transformable::getDimension()
{
    return new Dimension3D(1,1,1);
}
 */


/*
 * returns the base vector described by our transforms
Vector3D * Transformable::getBaseVector()
{
    return new Vector3D(1,1,1);
}
 */


/*
 * pushes all subtransforms
 */
void Transformable::push()
{
	_stretch->push();
	_scale->push();
	_orientation->push();
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

	_stretch->pushInverse();

	_orientation->pushInverse();
}


/*
 * pops all subtransforms
 */
void Transformable::pop()
{
	_orientation->pop();
	_scale->pop();
	_stretch->pop();
}


/*
 * return the translation as a vector
 */
Vector3D * Transformable::getTranslation()
{
	return _orientation->getTranslation();
}


/* 
 * increment the position values
 */
void Transformable::incrementTranslation(Vector3D * position, InterpolationEngine * interpolation)
{
	_orientation->incrementTranslation(position, interpolation);
}


/* 
 * increment the position values
 */
void Transformable::incrementTranslation(Vector3D * position)
{
	_orientation->incrementTranslation(position);
}


/* 
 * set the position values
 */
void Transformable::setTranslation(Vector3D * position, InterpolationEngine * interpolation)
{
	_orientation->setTranslation(position, interpolation);
}


/* 
 * set the position values
 */
void Transformable::setTranslation(Vector3D * position)
{
	_orientation->setTranslation(position);
}


/*
 * 
 */
void Transformable::incrementScalar(Vector3D * scalar)
{
	_transformed = true;
    _scale->increment(scalar);
}


/*
 * 
 */
void Transformable::incrementScalar(Vector3D * scalar, InterpolationEngine * interpolation)
{
	_transformed = true;
    _scale->increment(scalar, interpolation);
}


/*
 * 
 */
void Transformable::setScalar(Vector3D * scalar)
{
	_transformed = true;
    _scale->set(scalar);
}


/*
 * 
 */
void Transformable::setScalar(Vector3D * scalar, InterpolationEngine * interpolation)
{
	_transformed = true;
    _scale->set(scalar, interpolation);
}


/*
 * 
 */
Vector3D * Transformable::getStretch()
{
	return _stretch->toVector();
}


/*
 * 
 */
void Transformable::setStretch(Vector3D * stretch, InterpolationEngine * interpolation) 
{
	_stretch->setOrigin(getBaseVector());

	_transformed = true;
	_stretch->set(stretch, interpolation);
}


/*
 * 
 */
void Transformable::setStretch(Vector3D * stretch)
{
	_stretch->setOrigin(getBaseVector());

	_transformed = true;
	_stretch->set(stretch);
}


/*
 * 
 */
void Transformable::incrementStretch(Vector3D * stretch, InterpolationEngine * interpolation) 
{
	_stretch->setOrigin(getBaseVector());

	_transformed = true;
	_stretch->increment(stretch, interpolation);
}


/*
 * 
 */
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
	_orientation->incrementRotation(dimension, angle, interpolation);
}


/*
 * increment the rotation value
 */
void Transformable::incrementRotation(const int dimension, float angle)
{
	_orientation->incrementRotation(dimension, angle);
}


/*
 * set the rotation value
 */
void Transformable::setRotation(const int dimension, float angle, InterpolationEngine * interpolation)
{
	_orientation->setRotation(dimension, angle, interpolation);
}


/*
 * set the rotation value
 */
void Transformable::setRotation(const int dimension, float angle)
{
	_orientation->setRotation(dimension, angle);
}


/*
 * change focus and adjust transforms
 */
void Transformable::setFocalPoint(Vector3D * point, InterpolationEngine * interpolation)
{
	_orientation->setFocalPoint(point, interpolation);
}

void Transformable::incrementFocalPoint(Vector3D * point, InterpolationEngine * interpolation)
{
	_orientation->incrementFocalPoint(point, interpolation);
}


void Transformable::incrementFocalPoint(Vector3D * point)
{
	_orientation->incrementFocalPoint(point);
}


/*
 * set fp
 */
void Transformable::setFocalPoint(Vector3D * point)
{
	_orientation->setFocalPoint(point);
}


/*
 * return the rotation value
 */
float Transformable::getRotation(const int dimension)
{
	_orientation->getRotation(dimension);
}


/*
 * return a clone of the focus point
 */
Vector3D * Transformable::getFocalPoint()
{
	_orientation->getFocalPoint();
}


/*
 * move camera along focal vector
 */
void Transformable::walk(float distance, InterpolationEngine * interpolation)
{
	_orientation->walk(distance, interpolation);
}


/*
 * apply a given orientation to this object
 */
void Transformable::setOrientation(Orientation *orient, InterpolationEngine * interpolation[4])
{
	_orientation->setTranslation(orient->getTranslation(), interpolation[0]);
	_orientation->setRotation(Orientation::THETA, orient->getRotation(Orientation::THETA), interpolation[1]);
	_orientation->setRotation(Orientation::PHI, orient->getRotation(Orientation::PHI), interpolation[2]);
	_orientation->setRotation(Orientation::ROLL, orient->getRotation(Orientation::ROLL), interpolation[3]);
}

/*
 * apply a given orientation with no interpolations
 */
void Transformable::setOrientation(Orientation *orient)
{
	_orientation->setTranslation(orient->getTranslation());
	_orientation->setRotation(Orientation::THETA, orient->getRotation(Orientation::THETA));
	_orientation->setRotation(Orientation::PHI, orient->getRotation(Orientation::PHI));
	_orientation->setRotation(Orientation::ROLL, orient->getRotation(Orientation::ROLL));
}

/*
 * apply a given orientation to this object
 */
void Transformable::incrementOrientation(Orientation *orient, InterpolationEngine * interpolation[4])
{
	_orientation->incrementTranslation(orient->getTranslation(), interpolation[0]);
	_orientation->incrementRotation(Orientation::THETA, orient->getRotation(Orientation::THETA), interpolation[1]);
	_orientation->incrementRotation(Orientation::PHI, orient->getRotation(Orientation::PHI), interpolation[2]);
	_orientation->incrementRotation(Orientation::ROLL, orient->getRotation(Orientation::ROLL), interpolation[3]);
}

/*
 * apply a given orientation with no interpolations
 */
void Transformable::incrementOrientation(Orientation *orient)
{
	_orientation->incrementTranslation(orient->getTranslation());
	_orientation->incrementRotation(Orientation::THETA, orient->getRotation(Orientation::THETA));
	_orientation->incrementRotation(Orientation::PHI, orient->getRotation(Orientation::PHI));
	_orientation->incrementRotation(Orientation::ROLL, orient->getRotation(Orientation::ROLL));
}



/*
 * print member info
 */
void Transformable::print()
{
	_orientation->print();

	cout << "scale_x="   << _scale->_xScale << 
		    "scale_y="   << _scale->_xScale   <<
		    "scale_z="   << _scale->_xScale  << endl;;
}


/*
 * print waypoint information
 */
void Transformable::printWaypoint()
{
	_orientation->printWaypoint();
}


/*
 * reset the transforms
 */
void Transformable::clear()
{
	_transformed = false;
	_orientation->clear();
}


/*
 * true if any Transforms have been modified
 */
bool Transformable::isTransformed()
{
	return _orientation->isTransformed();
}

}

