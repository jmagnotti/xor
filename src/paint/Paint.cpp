#include "Paint.h"


namespace XOR {

Paint::Paint(Paint * paint)
{
    clone(paint);
}


/*
 * paint initializer
 */
void Paint::buildPaint(const float colorTo[4], const float colorFrom[4], 
        const int gradientType, float autoGrad, Texture * texture)
{
    //cout << "Passed in as: " << endl;

    //cout << "Using paint: r: " << colorTo[0] << ", g: " << colorTo[1] << ", b: " << colorTo[2] << endl;
    //cout << "Using paint: r: " << colorFrom[0] << ", g: " << colorFrom[1] << ", b: " << colorFrom[2] << endl;
    //cout << "---" << endl;

    for(int i=0; i<4; i++) {
        _colorTo[i]   = colorTo[i];
        _colorFrom[i] = colorFrom[i];
    }

    _gradientType = gradientType;
    _autoGradient = autoGrad;

    _textured = false;
    if (texture != NULL)
        _textured = true;

    _texture = texture;

    // build the color diff array if there is to be gradient painting
    if (_gradientType != NO_GRADIENT) {
 
        // if an autogradient is specified, then set the from and to colors
        if (_autoGradient > 0.0f)
            recalculateGradient();

        buildDifferenceArray();
    }

    //cout << "Using paint: r: " << colorTo[0] << ", g: " << colorTo[1] << ", b: " << colorTo[2] << endl;
    //cout << "Using paint: r: " << colorFrom[0] << ", g: " << colorFrom[1] << ", b: " << colorFrom[2] << endl;
}


/*
 * default constructor
 */
Paint::Paint(void)
{
    setColorTo(Color::WHITE);
    buildPaint(_colorTo, _colorTo, NO_GRADIENT, -1, NULL);
}


/*
 * Explicit constructor
 */
Paint::Paint(float red, float green, float blue)
{
	_colorFrom[0] = red;
	_colorFrom[1] = green;
	_colorFrom[2] = blue;
	_colorFrom[3] = 1.0f;

    buildPaint(_colorTo, _colorTo, NO_GRADIENT, -1, NULL);
}


/*
 * Explicit Constructor
 */
Paint::Paint(float red, float green, float blue, const int gradientType)
{
	_colorTo[0] = red;
	_colorTo[1] = green;
	_colorTo[2] = blue;
	_colorTo[3] = 1.0f;

    buildPaint(_colorTo, _colorTo, gradientType, .3f, NULL);
}


/*
 * Explicit Constructor
 * Creates a Paint object with the specified color
 */
Paint::Paint(const float color[4])
{
    buildPaint(color, color, NO_GRADIENT, -1, NULL);
}


/*
 * Explicit Constructor
 */
Paint::Paint(const float color[4], const int gradientType)
{
    buildPaint(color, color, gradientType, .3f, NULL);
}


/*
 * Explicit Constructor
 * Creates a Paint object with the specified gradient
 */
Paint::Paint(const float startColor[4], const float endColor[4], int gradientType)
{
    buildPaint(startColor, endColor, gradientType, -1, NULL);
}


/*
 * Explicit Constructor
 * Creates a Paint object with the specified gradient
 */
Paint::Paint(const float startColor[4], const float endColor[4], int gradientType, Texture * tex)
{
    buildPaint(startColor, endColor, gradientType, -1, tex);
}


/*
 * Explicit Constructor
 */
Paint::Paint(const float startColor[4], int gradientType, Texture *  tex)
{
    buildPaint(startColor, startColor, gradientType, .3f, tex);
}


/*
 * Explicit Constructor.
 * Creates a Paint object with a texture and a white color
 */
Paint::Paint(Texture * tex)
{
    setColorTo(Color::WHITE);
    buildPaint(_colorTo, _colorTo, NO_GRADIENT, -1, tex);
}


/*
 * Explicit Constructor
 */
Paint::Paint(const float color[4], Texture * tex)
{
    buildPaint(color, color, NO_GRADIENT, -1, tex);
}


/*
 * set the appropriate color 
 */
void Paint::activateColorAtPosition(Vector3D * scale)
{
    /*
        cout <<  "  r: " << scale->getY() << " x " << _colorDiff[0] << " + " << _colorFrom[0] << endl;
        cout <<  "  g: " << scale->getY() << " x " << _colorDiff[1] << " + " << _colorFrom[1] << endl;
        cout <<  "  b: " << scale->getY() << " x " << _colorDiff[2] << " + " << _colorFrom[2] << endl;
    */

    switch(_gradientType) {
        case LENGTH_BASED:
            glColor4f(  scale->getX() * _colorDiff[0] + _colorFrom[0],
                        scale->getX() * _colorDiff[1] + _colorFrom[1],
                        scale->getX() * _colorDiff[2] + _colorFrom[2],
                        scale->getX() * _colorDiff[3] + _colorFrom[3] );
            break;

        case HEIGHT_BASED:
            glColor4f(  scale->getY() * _colorDiff[0] + _colorFrom[0],
                        scale->getY() * _colorDiff[1] + _colorFrom[1], 
                        scale->getY() * _colorDiff[2] + _colorFrom[2],
                        scale->getY() * _colorDiff[3] + _colorFrom[3] );
            break;

        case DEPTH_BASED:
            glColor4f(  scale->getZ() * _colorDiff[0] + _colorFrom[0],
                        scale->getZ() * _colorDiff[1] + _colorFrom[1], 
                        scale->getZ() * _colorDiff[2] + _colorFrom[2],
                        scale->getZ() * _colorDiff[3] + _colorFrom[3] );
            break; 

        default:
            glColor4fv(_colorTo);
            break;
    }
}


/*
 *
 */
void Paint::activateTextureAtPosition(Vector2D * scale)
{
    if (! _textured)
        return;

    glTexCoord2f(scale->getX(), scale->getY());    
}


/*
 * disable texture if need be
 */
void Paint::deactivate()
{
    if (_textured) 
        Texture::DisableTextures();
}


/*
 * enable texture if need be
 */
void Paint::activate()
{
    if (_textured) {
        Texture::EnableTextures();
        _texture->setActive();
    }
}

/*
 * basic info
 */
void Paint::print()
{
    cout << "Gradient type: " << getGradientType() << endl << "Colors:\t";

    for(int i=0; i<4; i++) 
        cout << _colorFrom[i] << " ";   

    cout << endl << "\t";

    for(int i=0; i<4; i++) 
        cout << _colorTo[i] << " ";   

    cout << endl << "Textured? " << isTextured() << endl;
    cout << "AutoGradient: " << getAutoGradient() << endl << endl;
}


/*
 * Recalculates the values for the gradient based 
 * on the values in autoGradient
 */
void Paint::recalculateGradient()
{
	if (_autoGradient < 0.0f)
		_autoGradient = .3f;

    // sanity check
    if (_gradientType != NO_GRADIENT) {

	    for (int i=0; i<3; i++)
		    _colorFrom[i] = _colorTo[i] * _autoGradient;

        // the default is not to make the alpha a gradient
        _colorFrom[3] = _colorTo[3];

        buildDifferenceArray();
    }
}


/*
 * sets tha alpha value of the to color
 */
void Paint::setColorToAlpha(float alpha)
{
    _colorTo[3] = alpha;
}


/*
 * set the alpha of the base color
 */
void Paint::setColorFromAlpha(float alpha)
{
    _colorFrom[3] = alpha;
}


/*
 * Sets the decrement value for the auto gradient
 */
void Paint::setAutoGradient(float autoGrad)	
{
	//check if different than current value to avoid extra calculations
	if (_autoGradient != autoGrad) {
		_autoGradient = autoGrad;		
		recalculateGradient();
	}
}


/*
 * Sets just the colorFrom
 */
void Paint::setColorFrom(const float ct[4])
{
    for (int i=0; i<4; i++)
        _colorFrom[i] = ct[i];
}


/*
 * Sets just the colorTo
 */
void Paint::setColorTo(const float ct[4])
{
    for (int i=0; i<4; i++)
        _colorTo[i] = ct[i];
}

void Paint::setColorTo(int which, float value)
{
    if (which >= 0 && which <= 4)
        _colorTo[which] = value;
}

void Paint::setColorFrom(int which, float value)
{
    if (which >=0 && which <= 4)
        _colorFrom[which] = value;
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




/*
 *
 */
void Paint::clone(Paint * other)
{
    _textured       = other->_textured;
    _texture        = other->_texture;

    setColorTo(other->_colorTo);
    setColorFrom(other->_colorFrom);

    _gradientType   = other->_gradientType;

    if (_gradientType != NO_GRADIENT)
        buildDifferenceArray();

    _autoGradient   = other->_autoGradient;
}


/*
 * return a copy of this paint
 */
Paint * Paint::clone()
{
    return new Paint(getColorTo(), getColorFrom(), _gradientType, getTexture());
}


/*
 * recalc the differences
 */
void Paint::buildDifferenceArray()
{
    for (int i=0; i<4; i++) 
        _colorDiff[i] = _colorTo[i] - _colorFrom[i];
}


//---GETTERS---//
bool		Paint::isTextured()			{	return _textured;		}
float		Paint::getAutoGradient()	{	return _autoGradient;	}
const int 	Paint::getGradientType()	{	return _gradientType;	}
float	*	Paint::getColorFrom()       {	return _colorFrom;		}
float	*	Paint::getColorTo()         {	return _colorTo;		}
Texture	*	Paint::getTexture()	const	{	return _texture;		}

}

