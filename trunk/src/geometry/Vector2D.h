#ifndef VECTOR2D_H
#define VECTOR2D_H


#include <string>


using namespace std;

namespace XOR {

/**
 * This class provides a convenient way to store the positions of 2D objects.
 */
class Vector2D
{

public:

    
	/**
	 * Creates a 2D vector with equal values for each dimension.
	 */
	Vector2D(float value);


	/**
	 * Creates a 2D vector with specific values for each dimension.
	 */
	Vector2D(float x, float y);


	/**
	 * Creates a 2D vector with specific values for each dimension.
	 */
    Vector2D(float points [2]);

	
	/**
	 * Return the X dimension
	 */
    float getX();


	/**
	 * Return the Y dimension
	 */
	float getY();

	/**
	 * Return the specified dimension. Performs checking -1 <
	 * dimension < 2. Returns 0 on failure.
	 */
    float get(int dimension);

	/*
	 * Returns the vec2d in array form
	 */
	float * toArray();

	/**
	 * Returns a string representation of the vector
	 */
    char * toString();


	/**
	 * Increment the value of the vector according to the parameter
	 */
    void increment(Vector2D * other);


	/**
	 * Increment the value of the vector according to the parameter
	 */
    void increment(float position[2]);


    /**
     * Addition operation
	 * Returns a new Vector representing the sum of the two vectors.
     */
	Vector2D * operator + (Vector2D * other);


    /**
     * Multiplication operation
	 * Returns a new Vector representing the product of the two vectors.
     */
	Vector2D * operator * (Vector2D * other);


    /**
     * Division operation
	 * Returns a new Vector representing the product of the two vectors.
     */
	Vector2D * operator / (Vector2D * other);


    /**
     * Subtraction operation
	 * Returns a new Vector representing the difference of the two vectors.
     */
	Vector2D * operator - (Vector2D * other);


	/**
	 * Returns a new vector that is -1*CurrentVector
	 */
	Vector2D * invert();


	/**
	 * change the position of the vector
	 */
	void setPosition(float position[2]);


	/**
	 * Clone the position from the other vector to this one.
	 */
	void clone(Vector2D * other);


    /**
     * Returns a clone of the current vector. Modifications to the returned Vector2D will not affect this vector.
     */
	Vector2D * clone();


private:

	float _position[2];

	Vector2D();

};

}

#endif			// VECTOR2D_H

