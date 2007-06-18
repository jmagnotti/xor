#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H


#include <vector>

#include "Object3D.h"
#include "../transform/Transform.h"
#include "../geometry/Dimension3D.h"
#include "../geometry/Vector3D.h"


using namespace std;

namespace XOR {

/**
 * A new way to do Transforms. Object gains transformation ability through
 * decoration. 
 *
 * @author John Magnotti
 * @author Michael Lam
 * @version 1.1
 */
class Transformable : public Object3D
{

public:

    Transformable(Object3D * obj);

    void addTransform(Transform * transform);

    Vector3D * getBaseVector();

    Dimension3D * getDimension();

    void removeTransform(Transform * transform);

    void render();

protected:

	// the object that gets decorated
    // camera needs access to this
	Object3D	* _object3d;

    // this is going to private once we fix camera
	Transformable();

    void renderObject();

    virtual void doTransform();

    virtual void undoTransform();

    virtual void doInverseTransform(); 

private:

    vector<Transform*> _transforms;

};

}

#endif			// TRANSFORMABLE_H

