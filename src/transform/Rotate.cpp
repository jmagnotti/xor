#include "Rotate.h"

namespace XOR {

const Vector3D * Rotate::PITCH  = new Vector3D(1,0,0);
const Vector3D * Rotate::YAW    = new Vector3D(0,1,0);
const Vector3D * Rotate::ROLL   = new Vector3D(0,0,1);
const Vector3D * Rotate::ORIGIN = new Vector3D(0,0,0);

/*
 * Destructor
 */
Rotate::~Rotate()
{
    delete _center;
    delete _centeringTranslate;
}

InterpolatedRotate::~InterpolatedRotate()
{
	if (_action != NULL)
		delete _action;
    
    //necessary ?
//    _steps.clear();
}

/*
 * Default Constructor
 */
Rotate::Rotate()
{
    _angle  = 0.0f;
    _xCoord = _yCoord = _zCoord = 0;
}


/*
 * Explicit constructor
 */
Rotate::Rotate(float angle, float x, float y, float z, const Vector3D * center)
{
    _center = center;
    _centeringTranslate = Translate::CreateTranslate((Vector3D*)_center);

	_angle  = angle;

	_xCoord	= x;
	_yCoord	= y;
	_zCoord	= z;
}

Rotate::Rotate(float angle, const Vector3D * axis, const Vector3D * center)
{
    _center = center;
    _centeringTranslate = Translate::CreateTranslate((Vector3D*)_center);

	_angle  = angle;

	_xCoord = axis->getX();
	_yCoord = axis->getY();
	_zCoord = axis->getZ();
}

/**
 * Clone copier
 */
void Rotate::clone(Rotate * other)
{
    _angle  = other->_angle;

    _center = other->_center;

    _xCoord = other->_xCoord;
    _yCoord = other->_yCoord;
    _zCoord = other->_zCoord;
}


/*
 * pushes a matrix then applies the rotate
 */
void Rotate::push()
{

    if (_center != Rotate::ORIGIN) {
        _centeringTranslate->push();
#ifdef DEBUG
        //Logger::GetInstance()->printTabs();
        cout << "Rotate::push()" << endl;
        //Logger::GetInstance()->incrementTabLevel();
#endif
        glPushMatrix();
        	glRotatef(_angle, _xCoord, _yCoord, _zCoord);

        _centeringTranslate->pushInverse();
    }
    else {
        glPushMatrix();
        glRotatef(_angle, _xCoord, _yCoord, _zCoord);
    }

}

void Rotate::pop()
{
	#ifdef DEBUG
		cout << "Rotate::pop()" << endl;
	#endif

    if (_center != Rotate::ORIGIN) {
        _centeringTranslate->pop();
        _centeringTranslate->pop();
    }

    Transform::pop();
}


/*
 * pushes a matrix then applies the rotate (in reverse)
 */
void Rotate::pushInverse()
{

    if (_center != Rotate::ORIGIN) {
        _centeringTranslate->pushInverse();
#ifdef DEBUG
        Logger::GetInstance()->printTabs();
        cout << "Rotate::pushInverse()" << endl;
        Logger::GetInstance()->incrementTabLevel();
#endif
        glPushMatrix();
        	glRotatef(-(_angle), _xCoord, _yCoord, _zCoord);

        _centeringTranslate->push();
    }
    else {
        glPushMatrix();
        glRotatef(-(_angle), _xCoord, _yCoord, _zCoord);
    }
}

void Rotate::print()
{
#ifdef DEBUG
    Logger::GetInstance()->printTabs();
#endif
    cout << "ang: " << _angle << ", x: " << _xCoord << ", y: " << _yCoord 
         << ", z: " << _zCoord << endl;
}

void Rotate::toIdentity()
{
    _angle = 0.0f;
}

Rotate * Rotate::CreateRotate(float angle, const Vector3D * axis, const Vector3D * center)
{
	return new ImmediateRotate(angle, axis, center);
}

Rotate * Rotate::CreateRotate(float angle, float x, float y, float z, const Vector3D * center)
{
	return new ImmediateRotate(angle, x, y, z, center);
}

Rotate * Rotate::CreateRotate(float angle, const Vector3D * axis, int milliseconds, const Vector3D * center)
{
	return new InterpolatedRotate(angle, axis, milliseconds, center);
}

Rotate * Rotate::CreateRotate(float angle, const Vector3D * axis, 
        int milliseconds, Action * action, const Vector3D * center)
{
	return new InterpolatedRotate(angle, axis, milliseconds, action, center);
}

Rotate * Rotate::CreateRotate(float angle, float x, float y, float z, int milliseconds, const Vector3D * center)
{
	return new InterpolatedRotate(angle, x, y, z, milliseconds, center);
}

Rotate * Rotate::CreateRotate(float angle, float x, float y, float z, 
        int milliseconds, Action * action, const Vector3D * center)
{
	return new InterpolatedRotate(angle, x, y, z, milliseconds, action, center);
}

//TODO Fill these in
void Rotate::transform(Vector3D * position){}
void Rotate::transform(Dimension3D * size){}
void Rotate::transform(Vector2D * position){}
void Rotate::transform(Dimension2D * size){}

float Rotate::getAngle()
{
	return _angle;
}

void InterpolatedRotate::push()
{
    interpolate();
    Rotate::push();
}

void Rotate::setAngle(float angle)
{
	_angle = angle;
}

void InterpolatedRotate::interpolate()
{
	if (_remaining > 0) {
		_angle += (*_steps)[_total - _remaining];

        -- _remaining;

        /*
        if (_remaining <= 0) {
            cout << "setting _angle to " << _target << " from " << _angle << endl;

            _angle = _target;

            */
        if (_action != NULL)
            _action->execute();
        //}
    }
}

void InterpolatedRotate::pushInverse()
{
    interpolate();
    Rotate::pushInverse();
}

/**
 * initializes InterpolatedRotate
 */
void InterpolatedRotate::build(float target, int milliseconds, Action * action)
{
    _total  = _remaining = Timer::millisecondsToFrames(milliseconds);
    _target = target;

    _steps = InterpolatorFactory::GetInstance()->
             getDefaultInterpolator()->build(target, _total);

    _action = action;
}

/**
 * CTORs for InterpolatedRotate
 */
InterpolatedRotate::InterpolatedRotate(float angle, const Vector3D * axis, int
        milliseconds, const Vector3D * center) :
    Rotate(0, axis, center) 
{
    build(angle, milliseconds, NULL);
}

InterpolatedRotate::InterpolatedRotate(float angle, const Vector3D * axis, int
        milliseconds, Action * action, const Vector3D * center) :
    Rotate(0, axis, center) 
{
    build(angle, milliseconds, action);
}

InterpolatedRotate::InterpolatedRotate(float angle, float x, float y, float z,
        int milliseconds, const Vector3D * center) :
    Rotate(0, x, y, z, center) 
{
    build(angle, milliseconds, NULL);
}

InterpolatedRotate::InterpolatedRotate(float angle, float x, float y, float z,
        int milliseconds, Action * action, const Vector3D * center) :
    Rotate(0, x, y, z, center) 
{
    build(angle, milliseconds, action);
}

/**
 * ImmediateRotates just pass through to Rotate
 */
ImmediateRotate::ImmediateRotate(float angle, const Vector3D * axis, const
        Vector3D * center) 
    : Rotate(angle, axis, center) {}

ImmediateRotate::ImmediateRotate(float angle, float x, float y, float z, const
        Vector3D * center) 
    : Rotate(angle, x, y, z, center) {}

}
