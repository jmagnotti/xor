#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <string>
#include <stdlib.h>
#include <iostream>

using namespace std;

namespace XOR
{

/**
 * This class provides a convenient way to store the positions of 3D objects.
 */
class Vector3D
{

public:

	/**
	 * Accessor constants. These are the preferred parameters to all 
	 * accessor methods that take const int. The compiler will inline these, 
	 * so no complaining about speed issues.
	 */
	static const int X;
	static const int Y;
	static const int Z;

	/**
	 * Returns a vector representing the min_x and min_y of the two vectors
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
	Vector3D(float points[3]);

	/**
	 * String constructor. space separated
	 */
	Vector3D(char * vals);

	/**
	 * Return the X dimension
	 */
	float getX() const;

	/**
	 * Return the Y dimension
	 */
	float getY() const;

	/**
	 * Return the Z dimension
	 */
	float getZ() const;

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
	void scale(Vector3D * other);

	/**
	 * Addition operation
	 * Returns a new Vector representing the sum of the two vectors.
	 */
	Vector3D * operator +(Vector3D * other);

	/**
	 * Addition operation
	 */
	Vector3D * operator +(float a);

	/**
	 * Multiplication operation
	 * Returns a new Vector representing the product of the two vectors.
	 */
	Vector3D * operator *(Vector3D * other);

	/**
	 * Multiplication operation
	 */
	Vector3D * operator *(float a);

	/**
	 * Division operation
	 * Returns a new Vector representing the product of the two vectors.
	 */
	Vector3D * operator /(Vector3D * other);

	/**
	 * Division operation
	 */
	Vector3D * operator /(float a);

	/**
	 * Subtraction operation
	 * Returns a new Vector representing the difference of the two vectors.
	 */
	Vector3D * operator -(Vector3D * other);

	/**
	 * Subtraction operation
	 */
	Vector3D * operator -(float a);

	/**
	 * equality operator
	 */
	bool operator ==(Vector3D * other);

	/**
	 * inequality operator
	 */
	bool operator !=(Vector3D * other);

	/**
	 * Returns a new vector where, for each current element, if it is 0, it
	 * becomes 1, otherwise it becomes 0; 
	 * @memory_usage The calling class is responsible for freeing the memory associated with the return value.
	 */
	Vector3D * complement();

	/**
	 * Returns a vector representing the absolute value of the current vector
	 * @memory_usage The calling class is responsible for freeing the memory associated with the return value.
	 */
	Vector3D * absoluteValue();

	/**
	 * Returns a new vector that is -1 * [A, B, C].
	 * @memory_usage The calling class is responsible for freeing the memory associated with the return value.
	 */
	Vector3D * invert();

	/**
	 * change the position of the vector
	 */
	void setPosition(float position[3]);
	// no checks on position, so use the constants above
	void setPosition(const int position, float value);
	void incrementPosition(const int position, float increment);

	/**
	 * Clone the position from the other vector to this one.
	 * @memory_usage The calling class is responsible for freeing the memory associated with the parameter.
	 */
	void clone(Vector3D * other);

	/**
	 * Returns a clone of the current vector. Modifications to the returned Vector3D will not affect this vector.
	 * @memory_usage The calling class is responsible for freeing the memory associated with the return value.
	 */
	Vector3D * clone();

private:

	float _position[3];

	Vector3D();

};

}

#endif			// VECTOR3D_H
