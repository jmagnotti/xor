#ifndef PAINT_H
#define PAINT_H


#include <string.h>

#include "../texture/Texture.h"
#include "../geometry/Vector3D.h"
#include "Color.h"


namespace XOR {

/**
 * Represents a paint job for a particular object. Contains information about
 * gradient painting as well. This should probably be turned into a singleton factory.
 */
class Paint
{

public: 

    /**
	 * Gradient constants.
     * Used to creates Paint objects with an auto gradient. This is used to simulate lighting. Basically 
     * the given color is used as the base color, then a darker color is used at the bottom.
     * Just how much darker is specified by the value of autoGradient.
     * 
     * These must be initialized in the Header file for the following reason,
     * borrowed from the gcc mailing list:
     * "The reason is that a switch statement is usually implemented with a
     * jump table, and so the values of each case label must be of integer type
     * and the compiler must be able to determine them at compile-time.  To
     * support this ability to implement switches with jump tables, the
     * standard forbids class objects from being used." 
     *
     * So RectangularPrism won't be able to switch based on gradient types. If
     * we define the values here, it can 'see' them and we are ok.
     */
	static const int NO_GRADIENT    = 0;
	static const int HEIGHT_BASED   = 1;
	static const int LENGTH_BASED   = 2;
	static const int DEPTH_BASED    = 3;


	//---CONSTRUCTORS---//
	Paint(void);
	Paint(Paint * paint);
    Paint(float red, float green, float blue);
    Paint(float red, float green, float blue, float alpha);
    Paint(float red, float green, float blue, const int gradientType);
    Paint(float red, float green, float blue, float alpha, const int gradientType);

    Paint(const float color[4]);
    Paint(const float startColor[4], const int gradientType);
    Paint(const float startColor[4], const float endColor[4], const int gradientType);

	Paint(Texture * tex);
	Paint(const float color[4], Texture * tex);
	Paint(const float startColor[4], const int gradientType, Texture *  tex);
	Paint(const float startColor[4], const float endColor[4], const int gradientType, Texture * tex);


	/**
	 * Explicit Constructor.
	 * This constructor is to be used only by the XML-to-GOR Tool. 
	 * Use the other constructors for other uses, as they are MUCH more efficient.
	 */
//	static Paint * CreatePaint(String, String, String, String, String, String);


	//---GETTERS---//
	bool		isTextured();
	float		getAutoGradient();
	int 		getGradientType();
	float	*	getColorFrom();
	float	*	getColorTo();
	Texture	*	getTexture();


    /**
     * Sets the current color context as a scaled value between ColorFrom and
     * ColorTo. For example, consider a Square from [0,0,0] to [1,1,0] with a
     * Black to White, Height-based gradient. Black will be set for all
     * positions in which the Y coordinate is 0. Concordantly, White will be
     * set for all positions in which the Y coordinate is 1. 
     *
     * @param scale The amount, relative to the object's maximum, of extent for
     * a given vertex.
     */
    void activateColorAtPosition(Vector3D * scale);


    /**
     * Texture coordinate mapping
     */
    void activateTextureAtPosition(Vector3D * scale);


    /**
     * Returns a paint with copies of the values for each member except for a
     * Texture if one is present.
     */
    Paint * clone();
    

    /*
     * copy values from other paint object, if present, a reference will be
     * made to the other Paint's Texture object.
     */
    void clone(Paint * other);
    
    
    void print();


	//---SETTERS---//
	void setAutoGradient	(float autoGrad);
	void setColorToAlpha	(float alpha);
	void setColorFromAlpha	(float alpha);
	void setColorFrom		(const float cf [4]);
	void setColorTo			(const float ct [4]);
	void setGradient		(int  grad);
	void setTexture			(Texture * tex);


private:

    /**
     * Resets colorTo and colorFrom values based on autoGradient.
     */
	void recalculateGradient();
	void buildDifferenceArray();


    /**
     * common area to build the paint object
     */
    void buildPaint(const float cf[4], const float ct[4], const int gradientType, float autoGrad, Texture * texture);

    
    Texture	*	_texture;
    
    bool		_textured;

	float		_colorFrom[4];
	float		_colorTo[4];	
	float		_colorDiff[4];	

    float		_autoGradient;	
    int			_gradientType;
    
};

}

#endif          // PAINT_H

