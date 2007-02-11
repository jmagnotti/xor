#include "String2D.h"


namespace XOR {

/*
 * Explicit Constructor
 */
String2D::String2D(char * string)
{

	_size = new Dimension2D(400,300);
	_text = string;

	_xpos = 10;
	_ypos = 20;

    for (int i=0; i<3; i++)
        _color[i] = Color::WHITE[i];
}


/*
 * Explicit Constructor.
 */
String2D::String2D(char * string, int xpos, int ypos, const float color [3])
{
    
    _size = Controller::GetInstance()->getViewer()->getWindowSize();
    
    _text = string;
    _xpos = xpos;
    _ypos = ypos;

    for (int i=0; i<3; i++)
        _color[i] = color[i];
}


/*
 * Explicit Constructor
 */
String2D::String2D(char * string, Dimension2D * size, int xpos, int ypos)
{	
	_text = string;
	_size = size;

	_xpos = xpos;
	_ypos = ypos;

    for (int i=0; i<3; i++)
        _color[i] = Color::WHITE[i];
}


/*
 * Explicit Constructor
 */
String2D::String2D(char * string, int winW, int winH, int xpos, int ypos)
{
	_text	= string;
	_size	= new Dimension2D(winW, winH);

	_xpos	= xpos;
	_ypos	= ypos;

    for (int i=0; i<3; i++)
        _color[i] = Color::WHITE[i];
}


/*
 * Returns the text of the string
 */
char * String2D::getText()
{
    return _text;
}


/* 
 * Set up 2D rendering, then render the string
 */
void String2D::render()
{
	glColor3fv(_color);

	//FIXME this needs to be in Object2D::render()
	BitmapFontUtil::beginRenderText((int)_size->getWidth(), (int)_size->getHeight());
	
	BitmapFontUtil::renderText(_xpos, _ypos, BITMAP_FONT_TYPE_HELVETICA_12, _text);
	
	//FIXME this needs to be in Object2D::render()
	BitmapFontUtil::endRenderText();
}


/*
 * Set the paint for the string
 */
void String2D::setText(char *text)
{
	_text = text;
}

Dimension3D * String2D::getDimension()
{
	return new Dimension3D(_size->getWidth(), _size->getHeight(), 0);
}

Vector3D * String2D::getBaseVector()
{
	return new Vector3D(_xpos, _ypos, 0);
}

}

