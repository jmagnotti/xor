#ifndef VECTOR3D_H
#define VECTOR3D_H


namespace XOR {

/**
 * This class provides a convenient way to store the positions of 3D objects.
 */
class Vector3D
{

public:

    
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
    float get(int dimension) const;

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
     * Addition operation
	 * Returns a new Vector representing the sum of the two vectors.
     */
	Vector3D * operator + (Vector3D * other);


    /**
     * Multiplication operation
	 * Returns a new Vector representing the product of the two vectors.
     */
	Vector3D * operator * (Vector3D * other);


    /**
     * Division operation
	 * Returns a new Vector representing the product of the two vectors.
     */
	Vector3D * operator / (Vector3D * other);


    /**
     * Subtraction operation
	 * Returns a new Vector representing the difference of the two vectors.
     */
	Vector3D * operator - (Vector3D * other);


	/**
	 * Returns a new vector that is -1*CurrentVector
	 */
	Vector3D * invert();


	/**
	 * change the position of the vector
	 */
	void setPosition(float position[3]);


	/**
	 * Clone the position from the other vector to this one.
	 */
	void clone(Vector3D * other);


private:

	float _position[3];

	Vector3D();

};

}

#endif			// VECTOR3D_H

