#include "Paint.h"


namespace XOR {

/**
 * default constructor
 */
Paint::Paint(void)
{
	textured = false;

	for (int i=0; i<3; i++) {
		colorFrom[i]	= 1.0f;
		colorTo[i]		= 1.0f;
	}

	gradientType = NO_GRADIENT;
}


/**
 * Explicit constructor
 */
Paint::Paint(float red, float green, float blue)
{
	textured = false;

	colorFrom[0] = red;
	colorFrom[1] = green;
	colorFrom[2] = blue;

	for (int i=0; i<3; i++)
		colorTo[i] = colorFrom[i];

	gradientType = NO_GRADIENT;
}


/**
 * Explicit Constructor
 * Creates a Paint object with the specified color
 */
Paint::Paint(const float color[3])
{
	textured = false;

	for (int i=0; i<3; i++)
	{
		colorFrom[i] = color[i];
		colorTo[i] = color[i];
	}

	gradientType = NO_GRADIENT;
}


/*
 * Explicit Constructor
 */
Paint::Paint(const float color[3], int gradient)
{
	textured = false;

	gradientType = gradient;
	
	for (int i=0; i<3; i++)
	{
		colorFrom[i] = color[i];
		colorTo[i] = color[i];
	}

	if (gradientType != NO_GRADIENT)
		recalculateGradient();	
}


/*
 * Explicit Constructor
 * Creates a Paint object with the specified gradient
 */
Paint::Paint(const float startColor[3], const float endColor[3], int gradient)
{
	textured = false;

	gradientType = gradient;

	for (int i=0; i<3; i++)
	{
		colorFrom[i]	= startColor[i];
		colorTo[i]		= endColor[i];
	}

}

/*
 * Explicit Constructor
 * Creates a Paint object with the specified gradient
 */
Paint::Paint(const float startColor[3], const float endColor[3], int gradType, Texture * tex)
{
	textured = true;

	for (int i=0; i<3; i++) {
		colorFrom[i]	= startColor[i];
		colorTo[i]		= endColor[i];
	}

	gradientType	= gradType;
	texture			= tex;

}


/*
 * Explicit Constructor
 */
Paint::Paint(const float startColor[3], int gradient, Texture *  tex)
{
	textured = true;
	
	for (int i=0; i<3; i++)
	{
		colorFrom[i]	= startColor[i];
		colorTo[i]		= startColor[i];
	}

	gradientType	= gradient;
	texture			= tex;

	if (gradientType != NO_GRADIENT)
		recalculateGradient();
}


/*
 * Explicit Constructor.
 * Creates a Paint object with a texture and a white color
 */
Paint::Paint(Texture * tex)
{
	textured = true;
	texture			= tex;

    setColorTo(Color::WHITE);
    setColorFrom(Color::WHITE);

	gradientType	= NO_GRADIENT;
}


/*
 * Explicit Constructor
 */
Paint::Paint(const float color[3], Texture * tex)
{
    textured = true;
    texture = tex;

    setColorFrom(color);
    setColorTo(color);
}



/**
 * Recalculates the values for the gradient based 
 * on the values in autoGradient
 */
void Paint::recalculateGradient()
{
	if (autoGradient == 0)
		autoGradient = .4f;


    if (gradientType != NO_GRADIENT) {
	    for (int i=0; i<3; i++)
		    colorFrom[i] = colorTo[i] * autoGradient;
    }
}


/**
 * Sets the decrement value for the auto gradient
 */
void Paint::setAutoGradient(float autoGrad)	
{
	//check if different than current value
	if (autoGradient != autoGrad) {
		autoGradient = autoGrad;		
		recalculateGradient();
	}
}


/*
 * Sets just the colorFrom
 */
void Paint::setColorFrom(const float ct[3])
{
    for (int i=0; i<3; i++)
        colorFrom[i] = ct[i];
}


/*
 * Sets just the colorTo
 */
void Paint::setColorTo(const float ct[3])
{
    for (int i=0; i<3; i++)
        colorTo[i] = ct[i];
}


/*
 * Sets the gradient type of the paint object
 */
void Paint::setGradient(int grad)				
{
	gradientType = grad; 
}


/*
 * Sets the texture to be used by the paint
 */
void Paint::setTexture(Texture *tex)
{
	textured = true;
	texture = tex;
}

//---GETTERS---//
bool		Paint::isTextured()			{	return textured;		}
float		Paint::getAutoGradient()	{	return autoGradient;	}
float	*	Paint::getColorFrom()		{	return colorFrom;		}
float	*	Paint::getColorTo()			{	return colorTo;			}
int			Paint::getGradientStyle()	{	return gradientType;	}
Texture	*	Paint::getTexture()			{	return texture;			}

}

