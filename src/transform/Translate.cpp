#include "Translate.h"

namespace XOR
{

/*
 * Destructor
 */
Translate::~Translate()
{
}

Translate::Translate(float x, float y, float z)
{
	_translation[0] = x;
	_translation[1] = y;
	_translation[2] = z;
}

Translate::Translate(Vector3D * position)
{
	for (int i=0; i<3; i++)
		_translation[i] = position->get(i);
}

/**
 * makes the translate an identity transform T[0,0,0]
 */
void Translate::toIdentity()
{
	for (int i=0; i<3; i++)
		_translation[i] = 0.0f;
}

void Translate::transform(Vector3D * position)
{
	position->increment(_translation);
}

void Translate::transform(Dimension3D * size)
{
	//translates do not affect dimensions
}

void Translate::transform(Vector2D * position)
{
	position->increment(_translation[0], _translation[1]);
}

void Translate::transform(Dimension2D * size)
{
	//translates do not affect dimensions
}

/* 
 * explicit constructor
 */
Translate * Translate::CreateTranslate(float x, float y, float z)
{
	return new ImmediateTranslate(x, y, z);
}

Translate * Translate::CreateTranslate(float x, float y, float z,
		int milliseconds)
{
	return new InterpolatedTranslate(x, y, z, milliseconds);
}

Translate * Translate::CreateTranslate(float x, float y, float z, int
milliseconds, Action * action)
{
	new InterpolatedTranslate(x, y, z, milliseconds, action);
}

/*
 * Explicit Constructor
 */
Translate * Translate::CreateTranslate(Vector3D * position)
{
	return new ImmediateTranslate(position);
}

Translate * Translate::CreateTranslate(Vector3D * position, int milliseconds)
{
	return new InterpolatedTranslate(position, milliseconds);
}

Translate * Translate::CreateTranslate(Vector3D * position, int milliseconds,
		Action * action)
{
	return new InterpolatedTranslate(position, milliseconds, action);
}

/*
 * Clone copier
 */
void Translate::clone(Translate * other)
{
	for (int i=0; i<3; i++)
		_translation[i] = other->_translation[i];
}

/* 
 * apply the translate
 */
void Translate::push()
{
	glPushMatrix();
	glTranslatef(_translation[0], _translation[1], _translation[2]);

#ifdef DEBUG
	Logger::GetInstance()->printTabs();
	cout << "Translate::push()" << endl;
	Logger::GetInstance()->incrementTabLevel();
	Logger::printTabs();
	cout << "pushed: " << _translation[0] << " " << _translation[1] << " " << _translation[2] << endl;
#endif
}

/* 
 * apply the translate in reverse
 */
void Translate::pushInverse()
{
	glPushMatrix();
	glTranslatef(-(_translation[0]), -(_translation[1]), -(_translation[2]));
#ifdef DEBUG 
	Logger::GetInstance()->printTabs();
	cout << "Translate::pushInverse()" << endl;
	Logger::GetInstance()->incrementTabLevel();
	Logger::GetInstance()->printTabs();
	cout << "pushed: -" << _translation[0] << " -" << _translation[1] << " -" << _translation[2] << endl;
#endif
}

Vector3D * Translate::toVector()
{
	return new Vector3D(_translation);
}

void Translate::setTranslation(Vector3D * position)
{
	_translation[0] = position->getX();
	_translation[1] = position->getY();
	_translation[2] = position->getZ();
}

void Translate::print()
{
	cout << "x: "<< _translation[0]<< ", y: "<< _translation[1]<< ", z: "
			<< _translation[2]<< endl;
}

void InterpolatedTranslate::push()
{
	interpolate();
	Translate::push();
}

/*
 *
 */
void InterpolatedTranslate::pushInverse()
{
	interpolate();
	Translate::pushInverse();
}

/*
 *
 */
void InterpolatedTranslate::interpolate()
{
	if (_remaining > 0)
	{

		_translation[0] += (*_steps)[_total - _remaining]->getX();
		_translation[1] += (*_steps)[_total - _remaining]->getY();
		_translation[2] += (*_steps)[_total - _remaining]->getZ();

		--_remaining;

		if (_remaining <= 0)
		{
			// this provides a reasonable degree of assurance that we won't
			// have float errors on object positions. But it is borked at the moment
			//_translation[0] = _target->getX();
			//_translation[1] = _target->getY();
			//_translation[2] = _target->getZ();

			if (_action != NULL) {
				_action->execute();
			}
		}
	}

}

/**
 * CTOR for InterpolatedTranslate
 */
InterpolatedTranslate::InterpolatedTranslate(Vector3D * position,
		int milliseconds, Action * action) :
	Translate(new Vector3D(0,0,0))
{
	build(position, milliseconds, action);
}

/**
 * CTOR for InterpolatedTranslate
 */
InterpolatedTranslate::InterpolatedTranslate(float x, float y, float z, int
milliseconds) :
	Translate(0, 0, 0)
{
	build(new Vector3D(x, y, z), milliseconds, NULL);
}

/**
 * CTOR for InterpolatedTranslate
 */
InterpolatedTranslate::InterpolatedTranslate(float x, float y, float z, int
milliseconds, Action * action) :
	Translate(0, 0, 0)
{
	build(new Vector3D(x, y, z), milliseconds, action);
}

/**
 * CTOR for InterpolatedTranslate
 */
InterpolatedTranslate::InterpolatedTranslate(Vector3D * position,
		int milliseconds) :
	Translate(new Vector3D(0,0,0))
{
	build(position, milliseconds, NULL);
}

/**
 * builder for InterpolatedTranslate
 */
void InterpolatedTranslate::build(Vector3D * target, int milliseconds,
		Action * action)
{
	_total = _remaining = Timer::millisecondsToFrames(milliseconds);
	_target = target;
	_steps = InterpolatorFactory::GetInstance()->
	getDefaultInterpolator()->build(target, _remaining);

	_action = action;
}

/**
 * def ctor
 */
ImmediateTranslate::ImmediateTranslate(Vector3D * position) :
	Translate(position)
{
}

/**
 * def ctor
 */
ImmediateTranslate::ImmediateTranslate(float x, float y, float z) :
	Translate(x, y, z)
{
}

}

