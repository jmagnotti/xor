#ifndef DIMENSION3D_H
#define DIMENSION3D_H


#include <stdlib.h>
#include <string>

#include "Dimension.h"
#include "Vector3D.h"


namespace XOR {

/**
 * This class provides a convenient way to store dimensions (not always extents) of 3D objects.
 * The original impetus for this class was to stop me from using Point3D for the same purpose.
 */
class Dimension3D : public Dimension
{

public:

	static const int WIDTH;
	static const int HEIGHT;
	static const int DEPTH;

	Dimension3D();
    

	Dimension3D(float rad);


	Dimension3D(float x, float y, float z);

    Dimension3D(float points [3]);


    /**
     * String constructor. Space separated
     */
    Dimension3D(char * vals);


	// Getters //
	int     getDimensionality();


    /*
    float   getX();
	float   getY();
	float   getZ();
    */

    float   getWidth();
	float   getHeight();
	float   getDepth();

    float get(const int dimension);

    Vector3D * toVector();

    void increment(Dimension3D * other);

    char * toString();

	void set(const int dimension, float value);

    /**
     * Addition operation
	Dimension3D * operator + (Dimension3D * dim);
     */


    /**
     * Subtraction operation
	Dimension3D * operator - (Dimension3D * dim);
     */

};

}

#endif			//DIMENSION3D_H

