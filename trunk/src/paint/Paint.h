#ifndef PAINT_H
#define PAINT_H


#include <string.h>

#include "../texture/Texture.h"
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
     */
	static const int NO_GRADIENT    = 0;
	static const int HEIGHT_BASED   = 1;
	static const int LENGTH_BASED   = 2;
	static const int DEPTH_BASED    = 3;


	//---CONSTRUCTORS---//
	Paint(void);
    Paint(float red, float green, float blue);

    Paint(const float color[3]);
    Paint(const float startColor[3],	int gradientType);
    Paint(const float startColor[3],	const float endColor[3],	int gradientType);

	Paint(Texture * tex);
	Paint(const float color[3],		Texture * tex);
	Paint(const float startColor[3],	int gradientType,	Texture *  tex);
	Paint(const float startColor[3],	const float endColor[3],	int gradientType,	Texture * tex);


	/**
	 * Explicit Constructor.
	 * This constructor is to be used only by the XML-to-GOR Tool. 
	 * Use the other constructors for other uses, as they are MUCH more efficient.
	 */
//	static Paint * CreatePaint(String, String, String, String, String, String);


	//---GETTERS---//
	bool		isTextured();
	float		getAutoGradient();
	float	*	getColorFrom();
	float	*	getColorTo();
	int			getGradientStyle();
	Texture	*	getTexture();


	//---SETTERS---//
	void setAutoGradient	(float autoGrad);
	void setColorFrom		(const float cf [3]);
	void setColorTo			(const float ct [3]);
	void setGradient		(int  grad);
	void setTexture			(Texture * tex);


protected:

    /**
     * Resets colorTo and colorFrom values based on autoGradient.
     */
	void recalculateGradient();

    
    Texture	*	texture;
    
    bool		textured;

	float		colorFrom[3];
	float		colorTo[3];	

    float		autoGradient;	
    int			gradientType;
};

}

#endif          // PAINT_H

