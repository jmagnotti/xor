#include "Translate.h"


namespace XOR {

/*
 * Destructor
 */
Translate::~Translate()
{}

Translate::Translate(float x, float y, float z)
{
    _translation[0] = x;
    _translation[1] = y;
    _translation[2] = z;
}

Translate::Translate(Vector3D * position)
{
    for(int i=0; i<3; i++)
        _translation[i] = position->get(i);
}


/**
 * makes the translate an identity transform T[0,0,0]
 */
void Translate::toIdentity()
{
    for(int i=0; i<3; i++)
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

Translate * Translate::CreateTranslate(float x, float y, float z, int milliseconds)
{
    return new InterpolatedTranslate(x, y, z, milliseconds);
}

Translate * Translate::CreateTranslate(float x, float y, float z, int milliseconds, Action * action)
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

Translate * Translate::CreateTranslate(Vector3D * position, int milliseconds, Action * action)
{
	return new InterpolatedTranslate(position, milliseconds, action);
}

/*
 * Clone copier
 */
void Translate::clone(Translate * other)
{
    for(int i=0; i<3; i++)
        _translation[i] = other->_translation[i];
}

/* 
 * apply the translate
 */
void Translate::push()
{
	glPushMatrix();
	glTranslatef(_translation[0], _translation[1], _translation[2]);
}


/* 
 * apply the translate in reverse
 */
void Translate::pushInverse()
{
	glPushMatrix();
	glTranslatef(-(_translation[0]), -(_translation[1]), -(_translation[2]));
}


Vector3D * Translate::toVector()
{
	return new Vector3D(_translation);
}

void Translate::print() 
{
	 cout << "x: "   << _translation[0] << ", y: " << _translation[1] 
		  << ", z: " << _translation[2] << endl;
}

void InterpolatedTranslate::push()
{
    if (_remaining > 0) {
        _translation[0] += _steps[_total - _remaining]->getX();
        _translation[1] += _steps[_total - _remaining]->getY();		
        _translation[2] += _steps[_total - _remaining]->getZ();		
        
        _remaining--;
    }

    Translate::push();
}


void InterpolatedTranslate::pushInverse()
{
    if (_remaining > 0) {
        _translation[0] += _steps[_total - _remaining]->getX();
        _translation[1] += _steps[_total - _remaining]->getY();		
        _translation[2] += _steps[_total - _remaining]->getZ();		
        
        _remaining--;
    }

    Translate::pushInverse();
}

/**
 * CTOR for InterpolatedTranslate
 */
InterpolatedTranslate::InterpolatedTranslate(Vector3D * position, int milliseconds, Action * action) : Translate(position)
{}

/**
 * CTOR for InterpolatedTranslate
 */
InterpolatedTranslate::InterpolatedTranslate(float x, float y, float z, int milliseconds) : 
		Translate(x, y, z) 
{
	//_target = new Vector3D(x,y,z);
}

InterpolatedTranslate::InterpolatedTranslate(float x, float y, float z, int milliseconds, Action * action) : 
		Translate(x, y, z) 
{
	//InterpolatorFactory::GetDefault()->setup(x, y, z, milliseconds, _steps);
}

InterpolatedTranslate::InterpolatedTranslate(Vector3D * position, int milliseconds) :
    Translate(position) 
{
	//InterpolatorFactory::getDefaultInterpolator()->setup(position, milliseconds, _steps);
}

ImmediateTranslate::ImmediateTranslate(Vector3D * position) 
    : Translate(position) {}

ImmediateTranslate::ImmediateTranslate(float x, float y, float z)
    : Translate(x, y, z) {}

}

