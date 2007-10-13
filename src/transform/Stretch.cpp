#include "Stretch.h"
#define DEBUG

namespace XOR {

/*
 * destructor
 */
Stretch::~Stretch()
{
    delete _translate;
    delete _scale;
}


/*
 * def cstr.
 */
Stretch::Stretch()
{
	_translate = Translate::CreateTranslate(0,0,0);
	_scale = new Scale();
}


/*
 * exp. cstr
 */
Stretch::Stretch(Vector3D * origin, Vector3D * stretch)
{
	_translate = Translate::CreateTranslate(origin);
	_scale = new Scale(stretch);
}


/*
 * push 3 matrices
 */
void Stretch::push()
{
	#ifdef DEBUG
		cout << "Stretch::push()" << endl;
	#endif

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
void Stretch::toIdentity()
{
	_translate->toIdentity();
	_scale->toIdentity();
}


/*
 * set the translate for the scale to use
 */
void Stretch::setOrigin(Vector3D * origin)
{
	delete _translate;
	_translate = Translate::CreateTranslate(origin);
}

void Stretch::transform(Vector3D * position) {}
void Stretch::transform(Dimension3D * size) {}

void Stretch::transform(Vector2D * position) {}
void Stretch::transform(Dimension2D * size) {}

}

