#include "String2D.h"


namespace XOR {

/*
 * Does all the work for building a string
 */
void String2D::build(char * string, int xpos, int ypos, const float color [3])
{
    _font = new BitmapFontType();
    *_font = BITMAP_FONT_TYPE_HELVETICA_12;
    _text = string;

	_xpos = xpos;
	_ypos = ypos;

    for (int i=0; i<3; i++)
        _color[i] = color[i];
}


/*
 * Explicit Constructor
 */
String2D::String2D(char * string)
{
	build(string, 10, 10, Color::WHITE);
}


/*
 * Explicit Constructor.
 */
String2D::String2D(char * string, int xpos, int ypos, const float color [3])
{
	build(string, xpos, ypos, color);
}


/*
 * Explicit Constructor
 */
String2D::String2D(char * string, int xpos, int ypos)
{	
	build(string, xpos, ypos, Color::WHITE);
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
void String2D::renderObject()
{
	glColor3fv(_color);
	BitmapFontUtil::renderText(_xpos, _ypos, _font, _text);
}


/*
 * Set the paint for the string
 */
void String2D::setText(char *text)
{
	_text = text;
}


/*
 * set the font
 */
void String2D::setFont(BitmapFontType font)
{
    *_font = font;
}


/*
 * increase the size if possible
 */
void String2D::increaseFontSize()
{
    if (*_font == BITMAP_FONT_TYPE_HELVETICA_10)
        *_font = BITMAP_FONT_TYPE_HELVETICA_12;
    else if (*_font == BITMAP_FONT_TYPE_HELVETICA_12)
        *_font = BITMAP_FONT_TYPE_HELVETICA_18;
    else if (*_font == BITMAP_FONT_TYPE_8_BY_13)
        *_font = BITMAP_FONT_TYPE_9_BY_15;
    else if (*_font == BITMAP_FONT_TYPE_TIMES_ROMAN_10)
        *_font = BITMAP_FONT_TYPE_TIMES_ROMAN_24;
}

void String2D::decreaseFontSize()
{
    if (*_font == BITMAP_FONT_TYPE_HELVETICA_18)
        *_font = BITMAP_FONT_TYPE_HELVETICA_12;
    else if (*_font == BITMAP_FONT_TYPE_HELVETICA_12)
        *_font = BITMAP_FONT_TYPE_HELVETICA_10;
    else if (*_font == BITMAP_FONT_TYPE_9_BY_15)
        *_font = BITMAP_FONT_TYPE_8_BY_13;
    else if (*_font == BITMAP_FONT_TYPE_TIMES_ROMAN_24)
        *_font = BITMAP_FONT_TYPE_TIMES_ROMAN_10;
}


/*
 * dummy return value
 */
Dimension2D * String2D::getDimension()
{
	return new Dimension2D(0,0);
}


/*
 * returns the point of origin for the string
 */
Vector2D * String2D::getBaseVector()
{
	return new Vector2D(_xpos, _ypos);
}

}

