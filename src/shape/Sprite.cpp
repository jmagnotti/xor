#include "Sprite.h"

namespace XOR {

/*
 *
 */
Sprite::Sprite()
{
	Controller::GetInstance()->getTimer()->addListener(this);
}


/*
 *
 */
Sprite::~Sprite()
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

}

