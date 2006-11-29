#ifndef DIMENSION3D_H
#define DIMENSION3D_H


#include "Dimension.h"


namespace XOR {

/**
 * This class provides a convenient way to store dimensions of 3D objects.
 * The original impetus for this class was to stop me from using Point3D for the same purpose.
 */
class Dimension3D : public Dimension
{

public:

	Dimension3D();
    

	Dimension3D(float rad);


	Dimension3D(float x, float y, float z);


	// Getters //
	int     getDimensionality();

    float   getWidth();
	float   getHeight();
	float   getDepth();


    /**
     * Addition operation
     */
	Dimension3D * operator + (Dimension3D * dim);


};

}

#endif			//DIMENSION3D_H

