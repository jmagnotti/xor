#ifndef DIMENSION2D_H
#define DIMENSION2D_H


#include "Dimension.h"


namespace XOR {

/**
 * This is a quick hack to allow for passing float[2]. 
 */
class Dimension2D : public Dimension
{

public:

    /*
     * Default Constructor
     */
	Dimension2D();


	/**
	 * Explicit Constructor
	 */
	Dimension2D(float width, float height);
    

    // Getters //
	int getDimensionality();

	float getWidth();
	float getHeight();


    // Setters //
	void setHeight(float height);
	void setWidth(float width);

};

}

#endif			// DIMENSION2D_H

