#include "Sprite.h"

namespace XOR {

	int Sprite::_idCounter = 0;

/*
 *
 */
Sprite::Sprite()
{
	_id = ++_idCounter;
}


/*
 *
 */
void Sprite::begin()
{
	Controller::GetInstance()->getTimer()->addListener(this);
}


/*
 *
 */
Sprite::~Sprite()
{}

void Sprite::end()
{
	Controller::GetInstance()->getTimer()->removeListener(this);
}

/*
 *
 */
void Sprite::handleTick()
{
	endFrame();
}

int Sprite::getID()
{
	return _id;
}

}

