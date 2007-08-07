#ifndef COLLISION_H_
#define COLLISION_H_

namespace XOR
{

class Collision
{
public:
	Collision();
	virtual ~Collision();

private:

	CollidableObject * _a, * _b;
	Vector3D * _pointOfImpact;
};

}

#endif /*COLLISION_H_*/
