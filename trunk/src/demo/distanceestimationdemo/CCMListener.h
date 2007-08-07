#ifndef CCMLISTENER_H_
#define CCMLISTENER_H_

namespace XOR
{

class CollidableObject
{
	
public:
	
	CollidableObject();
	
	virtual ~CollidableObject();

	virtual void handleCollision(Collision * collision)=0;
	
	virtual Vector3D * getMovementVector()=0;
	
	virtual Vector3D * getCurrentPosition()=0;
};

}

#endif /*CCMLISTENER_H_*/
