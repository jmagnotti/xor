#include "Stretch.h"


namespace XOR {

/*
 * def cstr.
 */
Stretch::Stretch()
{
	_translate = new Translate(0,0,0);
	_scale = new Scale();
}


/*
 * exp. cstr
 */
Stretch::Stretch(Vector3D * origin, Vector3D * stretch)
{
	_translate = new Translate(origin);
	_scale = new Scale(stretch);
}


/*
 * push 3 matrices
 */
void Stretch::push()
{
	_translate->pushInverse();
	_scale->push();
	_translate->push();
}


/*
 * push shrink
 */
void Stretch::pushInverse()
{
	_translate->pushInverse();
	_scale->pushInverse();
	_translate->push();
}


/*
 * to vector3D
 */
Vector3D * Stretch::toVector()
{
	_scale->toVector();
}


/*
 * pop 3 matrices
 */
void Stretch::pop()
{
	_translate->pop();
	_scale->pop();
	_translate->pop(); 
}

/*
 * nullify the effect of the stretch
 */
void Stretch::clear()
{
	_translate->clear();
	_scale->clear();
}


/*
 * set the scale
 */
void Stretch::set(Vector3D * stretch)
{
	_scale->set(stretch);
}


/*
 * set the scale
 */
void Stretch::set(Vector3D * stretch, InterpolationEngine * interpolation)
{
	_scale->set(stretch, interpolation);
}


/*
 * increment the scale
 */
void Stretch::increment(Vector3D * stretch)
{
	_scale->increment(stretch);
}


/*
 * increment the scale
 */
void Stretch::increment(Vector3D * stretch, InterpolationEngine * interpolation)
{
	_scale->increment(stretch, interpolation);
}


/*
 * set the translate for the scale to use
 */
void Stretch::setOrigin(Vector3D * origin)
{
	delete _translate;
	_translate = new Translate(origin);
}

}

