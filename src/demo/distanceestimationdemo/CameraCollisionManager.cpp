#include "CollisionManager.h"

CameraCollisionManager * CameraCollisionManager::_collisionManager = NULL;

CameraCollisionManager * CameraCollisionManager::GetInstance()
{
	if (_collisionManager == NULL)
		_collisionManager = new CameraCollisionManager();

	return _collisionManager;
}

void CameraCollisionManager::handleTick()
{
	checkForCollision();
}

CameraCollisionManager::CameraCollisionManager()
{
}

CameraCollisionManager::~CameraCollisionManager()
{
}

/**
 * Adds a listener
 */
void CameraCollisionManager::addListener(CollidableObject * listener)
{
	_listeners.push_back(listener);
}

/**
 * Removes a listener from the pool.
 */

CollidableObject * CameraCollisionManager::removeListener(CollidableObject * listener)
{
	bool removed = false;

	list<CollidableObject*>::iterator iter = _listeners.begin();
	list<CollidableObject*>::iterator finish = _listeners.end();

	while (!removed && iter != finish) {
		if (*iter == listener) {
			_listeners.erase(iter);
			removed = true;
		}
		else {
			++iter;
		}
	}
}

/**
 * Notifies Listeners of an event (push notification)
 */
void CameraCollisionManager::checkForCollision()
{

}
