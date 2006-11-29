#ifndef DIMENSION_H
#define DIMENSION_H


namespace XOR {

/**
 * Base class for dimension objects.
 */
class Dimension
{

public:

	/**
	 * Useful for determining the child class, since cpp doesn't have reflection.
     * Also used for reducing methods that only differ in their extent.
	 */
	inline virtual int getDimensionality()=0;

    /**
     * Clones the other dimensions values into this one. Does it's best to always copy some values. 
     * Will copy min(this.getDimensionality(), other.getDimensionality()) values;
     */
    void clone(Dimension * other);
	
    /**
     * Scales the given dimension
     */
	void scale(float scale); 


    /**
     * Returns the largest value in the dimension.
     */
    float getLargestSize();


    /**
     * Returns the smallest value in the dimension.
     */
    float getSmallestSize();


    /**
     * Returns the dimension formatted as an array
     */
    float * toArray();


protected:

	float * _dimension;

};

}

#endif			// DIMENSION_H

