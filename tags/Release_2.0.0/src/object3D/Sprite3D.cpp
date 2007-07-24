#include "Sprite3D.h"

namespace XOR {

int Sprite3D::_idCounter = 0;

/*
 *
 */
Sprite3D::Sprite3D()
{
	_id = ++_idCounter;
}


/*
 *
 */
void Sprite3D::begin()
{
	Controller::GetInstance()->getTimer()->addListener(this);
}


/*
 *
 */
Sprite3D::~Sprite3D()
{}

void Sprite3D::end()
{
	Controller::GetInstance()->getTimer()->removeListener(this);
}

/*
 *
 */
void Sprite3D::handleTick()
{
	endFrame();
	notifyListeners();
}

int Sprite3D::getID()
{
	return _id;
}

void Sprite3D::addListener(Sprite3DListener * sl)
{
	_listeners.push_back(sl);
}

void Sprite3D::removeListener(Sprite3DListener * sl)
{
    bool removed = false;

    list<Sprite3DListener*>::iterator iter   = _listeners.begin();
    list<Sprite3DListener*>::iterator finish = _listeners.end();

    while (!removed && iter != finish) {
        if (*iter == sl) {
			_listeners.erase(iter);
            removed = true;
		}
		else {
			++iter;
		}
    }

}


void Sprite3D::notifyListeners()
{
    list<Sprite3DListener*>::iterator iter   = _listeners.begin();
	list<Sprite3DListener*>::iterator next   = _listeners.begin();
    list<Sprite3DListener*>::iterator finish = _listeners.end();

    while (iter != finish) {
		++next;
		(*iter)->handlePositionChange(getBaseVector(), getID());
        iter = next;
    }
}

}

