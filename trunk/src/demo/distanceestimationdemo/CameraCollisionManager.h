#ifndef CAMERACOLLISIONMANAGER_H
#define CAMERACOLLISIONMANAGER_H

#include "TimerListener.h"
namespace XOR
{
class CameraCollisionManager : public CameraListener
{
public:

	virtual ~CameraCollisionManager();

	/**
	 * Singleton Accessor.
	 */
	CameraCollisionManager * GetInstance();

	void addListener(CollidableObject * listener);

	CollidableObject * removeListener(CollidableObject * listener);

	/**
	 * Automatically called on every camera movement. Interested objects can 
	 * call this method if they are moving to force another check with the camera.
	 */
	void checkForCollision();

private:

	static CameraCollisionManager * _cameraCollisionManager;

	CameraCollisionManager();

};

}
#endif			// CAMERACOLLISIONMANAGER_H
