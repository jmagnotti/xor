#ifndef VECTOR3D_H
#define VECTOR3D_H


#include <string>


using namespace std;

namespace XOR {

/**
 * This class provides a convenient way to store the positions of 3D objects.
 */
class Vector3D
{

public:

    /**
     * Returns a vector representing the min_x and min_x of the two vectors
     */
    static Vector3D * Min(Vector3D * a, Vector3D * b);


    /**
     * Returns a vector representing the max_x and max_x of the two vectors
     */
    static Vector3D * Max(Vector3D * a, Vector3D * b);
    

	/**
	 * Creates a 3D vector with equal values for each dimension.
	 */
	Vector3D(float value);


	/**
	 * Creates a 3D vector with specific values for each dimension.
	 */
	Vector3D(float x, float y, float z);

	/**
	 * Creates a 3D vector with specific values for each dimension.
	 */
    Vector3D(float points [3]);

	
	/**
	 * Return the X dimension
	 */
    float getX();


	/**
	 * Return the Y dimension
	 */
	float getY();


	/**
	 * Return the Z dimension
	 */
	float getZ();


	/**
	 * Return the specified dimension. Performs checking -1 <
	 * dimension < 3. Returns 0 on failure.
	 */
    float get(int dimension);

	/*
	 * Returns the vec3d in array form
	 */
	float * toArray();

	/**
	 * Returns a string representation of the vector
	 */
    char * toString();




	/**
	 * Increment the value of the vector according to the parameter
	 */
    void increment(Vector3D * other);


	/**
	 * Increment the value of the vector according to the parameter
	 */
    void increment(float position[3]);


    /**
     * Multiply each element by the corresponding element in the given
     * Vector3D.
     */
    void scale (Vector3D * other);


    /**
     * Addition operation
	 * Returns a new Vector representing the sum of the two vectors.
     */
	Vector3D * operator + (Vector3D * other);


    /**
     * Addition operation
     */
	Vector3D * operator + (float a);


    /**
     * Multiplication operation
	 * Returns a new Vector representing the product of the two vectors.
     */
	Vector3D * operator * (Vector3D * other);


    /**
     * Multiplication operation
     */
	Vector3D * operator * (float a);


    /**
     * Division operation
	 * Returns a new Vector representing the product of the two vectors.
     */
	Vector3D * operator / (Vector3D * other);


    /**
     * Division operation
     */
	Vector3D * operator / (float a);

    /**
     * Subtraction operation
	 * Returns a new Vector representing the difference of the two vectors.
     */
	Vector3D * operator - (Vector3D * other);


    /**
     * Subtraction operation
     */
	Vector3D * operator - (float a);


    /**
     * equality operator
     */
    bool operator == (Vector3D * other);


    /**
     * inequality operator
     */
    bool operator != (Vector3D * other);


    /**
     * Returns a new vector where, for each current element, if it is 0, it
     * becomes 1, otherwise it becomes 0;
     */
    Vector3D * complement();


    /**
     * Returns a vector representing the absolute value of the current vector
     */
    Vector3D * absoluteValue();


	/**
	 * Returns a new vector that is -1 * CurrentVector
	 */
	Vector3D * invert();


	/**
	 * change the position of the vector
	 */
	void setPosition(float position[3]);
	void setPosition(int position, float value);


	/**
	 * Clone the position from the other vector to this one.
	 */
	void clone(Vector3D * other);


    /**
     * Returns a clone of the current vector. Modifications to the returned Vector3D will not affect this vector.
     */
	Vector3D * clone();


private:

	float _position[3];

	Vector3D();

};

}

#endif			// VECTOR3D_H

