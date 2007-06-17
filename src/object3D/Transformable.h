#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H
namespace XOR {

/**
 *
 */
class Transformable
{
public:
    Transformable(Object3D * obj);

    void addTransform(Transform * transform);

    Dimension3D* getBaseVector();

    Dimension3D* getDimension();

    void removeTransform(Transform * transform);

    void render();

private:

    void virtual doTransform();

    void virtual undoTransform();

	Transformable();

	// the object that gets decorated
	Object3D	* _object3d;
};

}

#endif			// TRANSFORMABLE_H

