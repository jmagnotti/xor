#include "Paint.h"


namespace XOR {

/**
 * default constructor
 */
Paint::Paint(void)
{
    _autoGradient = .3f;
	_textured = false;

	for (int i=0; i<3; i++) {
		_colorFrom[i]	= 1.0f;
		_colorTo[i]		= 1.0f;
	}

	_gradientType = NO_GRADIENT;
}


/**
 * Explicit constructor
 */
Paint::Paint(float red, float green, float blue)
{
	_autoGradient = .3f;
    _textured = false;

	_colorFrom[0] = red;
	_colorFrom[1] = green;
	_colorFrom[2] = blue;

	for (int i=0; i<3; i++)
		_colorTo[i] = _colorFrom[i];

	_gradientType = NO_GRADIENT;
}


/**
 * Explicit Constructor
 */
Paint::Paint(float red, float green, float blue, const int gradientType)
{
	_autoGradient = .3f;
    _textured = false;

	_colorTo[0] = red;
	_colorTo[1] = green;
	_colorTo[2] = blue;

	_gradientType = gradientType;


	if (_gradientType != NO_GRADIENT)
		recalculateGradient();	
    else
        for (int i=0; i<3; i++)
            _colorFrom[i] = _colorTo[i];
}


/**
 * Explicit Constructor
 * Creates a Paint object with the specified color
 */
Paint::Paint(const float color[3])
{
    _autoGradient = .3f;
	_textured = false;

	for (int i=0; i<3; i++) {
		_colorFrom[i] = color[i];
		_colorTo[i] = color[i];
	}

	_gradientType = NO_GRADIENT;
}


/*
 * Explicit Constructor
 */
Paint::Paint(const float color[3], int gradient)
{
    _autoGradient = .3f;
	_textured = false;
    
	_gradientType = gradient;
	
	for (int i=0; i<3; i++) {
		_colorFrom[i] = color[i];
		_colorTo[i] = color[i];
	}

	if (_gradientType != NO_GRADIENT)
		recalculateGradient();	
}


/*
 * Explicit Constructor
 * Creates a Paint object with the specified gradient
 */
Paint::Paint(const float startColor[3], const float endColor[3], int gradient)
{
    _autoGradient = .3f;
	_textured = false;

	_gradientType = gradient;

	for (int i=0; i<3; i++)
	{
		_colorFrom[i]	= startColor[i];
		_colorTo[i]		= endColor[i];
	}

}

/*
 * Explicit Constructor
 * Creates a Paint object with the specified gradient
 */
Paint::Paint(const float startColor[3], const float endColor[3], int gradType, Texture * tex)
{
    _autoGradient = .3f;
	_textured = true;

	for (int i=0; i<3; i++) {
		_colorFrom[i]	= startColor[i];
		_colorTo[i]		= endColor[i];
	}

	_gradientType	= gradType;
	_texture			= tex;

}


/*
 * Explicit Constructor
 */
Paint::Paint(const float startColor[3], int gradient, Texture *  tex)
{
    _autoGradient = .3f;
	_textured = true;
	
	for (int i=0; i<3; i++)
	{
		_colorFrom[i]	= startColor[i];
		_colorTo[i]		= startColor[i];
	}

	_gradientType	= gradient;
	_texture			= tex;

	if (_gradientType != NO_GRADIENT)
		recalculateGradient();
}


/*
 * Explicit Constructor.
 * Creates a Paint object with a texture and a white color
 */
Paint::Paint(Texture * tex)
{
    _autoGradient = .3f;
	_textured = true;
	_texture			= tex;

    setColorTo(Color::WHITE);
    setColorFrom(Color::WHITE);

	_gradientType	= NO_GRADIENT;
}


/*
 * Explicit Constructor
 */
Paint::Paint(const float color[3], Texture * tex)
{
    _autoGradient = .3f;
    _textured = true;
    _texture = tex;

    setColorFrom(color);
    setColorTo(color);
}



/*
 * basic info
 */
void Paint::print()
{
    cout << "Gradient type: " << _gradientType << endl << "Colors:\t";

    for(int i=0; i<3; i++) 
        cout << _colorFrom[i] << " ";   

    cout << endl << "\t";

    for(int i=0; i<3; i++) 
        cout << _colorTo[i] << " ";   

    cout << endl << "Textured? " << isTextured() << endl;
    cout << "AutoGradient: " << getAutoGradient() << endl << endl;
}


/**
 * Recalculates the values for the gradient based 
 * on the values in autoGradient
 */
void Paint::recalculateGradient()
{
	if (_autoGradient == 0)
		_autoGradient = .4f;


    if (_gradientType != NO_GRADIENT) {
	    for (int i=0; i<3; i++)
		    _colorFrom[i] = _colorTo[i] * _autoGradient;
    }
}


/**
 * Sets the decrement value for the auto gradient
 */
void Paint::setAutoGradient(float autoGrad)	
{
	//check if different than current value
	if (_autoGradient != autoGrad) {
		_autoGradient = autoGrad;		
		recalculateGradient();
	}
}


/*
 * Sets just the colorFrom
 */
void Paint::setColorFrom(const float ct[3])
{
    for (int i=0; i<3; i++)
        _colorFrom[i] = ct[i];
}


/*
 * Sets just the colorTo
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
float	*	Paint::getColorTo()			{	return _colorTo;			}
int			Paint::getGradientStyle()	{	return _gradientType;	}
Texture	*	Paint::getTexture()			{	return _texture;			}

}

