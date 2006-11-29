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

    _paint	= new Paint(Color::WHITE);
}


/*
 * Explicit Constructor.
 */
String2D::String2D(char * string, int xpos, int ypos, Paint *p)
{
    
    _size = Controller::GetInstance()->getViewer()->getWindowSize();
    
    _text = string;
    _xpos = xpos;
    _ypos = ypos;

    _paint = p != NULL ? p : new Paint(Color::WHITE);
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

    _paint = new Paint(Color::WHITE);
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

    _paint	= new Paint(Color::WHITE);
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
	glColor3fv(_paint->getColorTo());

	BitmapFontUtil::beginRenderText(_size->getWidth(), _size->getHeight());
	
	BitmapFontUtil::renderText(_xpos, _ypos, BITMAP_FONT_TYPE_HELVETICA_12, _text);
	
	BitmapFontUtil::endRenderText();
}



/*
 * Set the paint for the string
 */
void String2D::setPaint(Paint *p)
{
	_paint = p;
}


/*
 * Set the paint for the string
 */
void String2D::setText(char *text)
{
	_text = text;
}

}

