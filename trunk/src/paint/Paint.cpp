#include "Paint.h"


namespace XOR {

/*
 * Purposely not initialized here. see Paint.h
    const int Paint::NO_GRADIENT    = 0;
    const int Paint::HEIGHT_BASED   = 1;
    const int Paint::LENGTH_BASED   = 2;
    const int Paint::DEPTH_BASED    = 3;
*/


/**
 * Explicit constructor
 */
Paint::Paint(float red, float green, float blue, int gradientType)
{
	_textured = false;

	_colorFrom[0] = red;
	_colorFrom[1] = green;
	_colorFrom[2] = blue;

	for (int i=0; i<3; i++)
		_colorTo[i] = _colorFrom[i];

	_gradientType = NO_GRADIENT;

	if (_gradientType != NO_GRADIENT)
		recalculateGradient();	
}


/*
 * Explicit Constructor
 */
Paint::Paint(const float color[3], int gradientType, Texture * tex)
{
    _textured = false;

    if (tex != NULL) {
        _textured   = true;
        _texture    = tex;
    }
	
	for (int i=0; i<3; i++) {
		_colorFrom[i]	= color[i];
		_colorTo[i]		= color[i];
	}

	_gradientType = gradientType;

	if (_gradientType != NO_GRADIENT)
		recalculateGradient();
} 


/*
 * Explicit Constructor
 * Creates a Paint object with the specified gradient
 */
Paint::Paint(const float startColor[3], const float endColor[3], int gradientType, Texture * tex)
{
    _textured = false;

    if (tex != NULL) {
        _textured   = true;
        _texture    = tex;
    }

	for (int i=0; i<3; i++) {
		_colorFrom[i]	= startColor[i];
		_colorTo[i]		= endColor[i];
	}

	_gradientType	= gradientType;

	if (_gradientType != NO_GRADIENT)
		recalculateGradient();	
}


/*
 * Exp const
 */
Paint::Paint(Texture *tex)
{
    _textured = true;

	for (int i=0; i<3; i++)
		_colorFrom[i] = _colorTo[i]	= Color::WHITE[i];

	_gradientType = NO_GRADIENT;
}


/**
 * Recalculates the values for the gradient based 
 * on the values in autoGradient
 */
void Paint::recalculateGradient()
{
    for (int i=0; i<3; i++)
        _colorFrom[i] = _colorTo[i] * _autoGradient;
}


/**
 * Sets the decrement value for the _auto gradient
 */
void Paint::setAutoGradient(float autoGrad)	
{
		_autoGradient = autoGrad;		
		recalculateGradient();
}


/*
 * Sets just the _colorFrom
 */
void Paint::setColorFrom(const float ct[3])
{
    for (int i=0; i<3; i++)
        _colorFrom[i] = ct[i];
}


/*
 * Sets just the _colorTo
 */
void Paint::setColorTo(const float ct[3])
{
    for (int i=0; i<3; i++)
        _colorTo[i] = ct[i];
}


/*
 * Sets the gradient type of the paint object
 */
void Paint::setGradient(int grad)				
{
	_gradientType = grad; 
}


/*
 * Sets the texture to be used by the paint
 */
void Paint::setTexture(Texture *tex)
{
	_textured = true;
	_texture = tex;
}


//---GETTERS---//
bool		Paint::isTextured()			{	return _textured;		}
float		Paint::getAutoGradient()	{	return _autoGradient;	}
float	*	Paint::getColorFrom()		{	return _colorFrom;		}
float	*	Paint::getColorTo()			{	return _colorTo;		}
int			Paint::getGradientStyle()	{	return _gradientType;	}
Texture	*	Paint::getTexture()			{	return _texture;		}

}

