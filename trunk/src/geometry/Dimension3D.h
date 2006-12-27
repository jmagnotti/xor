#ifndef DIMENSION3D_H
#define DIMENSION3D_H


#include "Dimension.h"


namespace XOR {

/**
 * This class provides a convenient way to store dimensions (not always extents) of 3D objects.
 * The original impetus for this class was to stop me from using Point3D for the same purpose.
 */
class Dimension3D : public Dimension
{

public:

	Dimension3D();
    

	Dimension3D(float rad);


	Dimension3D(float x, float y, float z);

    Dimension3D(float points [3]);

	// Getters //
	int     getDimensionality();

    float   getX();
	float   getY();
	float   getZ();

    float   getWidth();
	float   getHeight();
	float   getDepth();

    float get(int dimension);

    float * getTranslation();

    void increment(Dimension3D * other);

    char * toString();

    /**
     * Addition operation
     */
	Dimension3D * operator + (Dimension3D * dim);


    /**
     * Subtraction operation
     */
	Dimension3D * operator - (Dimension3D * dim);

};

}

#endif			//DIMENSION3D_H

