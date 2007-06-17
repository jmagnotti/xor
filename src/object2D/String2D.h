#ifndef STRING2D_H
#define STRING2D_H


#include <string.h>
#include "../geometry/Vector2D.h"
#include "../geometry/Dimension2D.h"
#include "../paint/Paint.h"
#include "../util/BitmapFontUtil.h"
#include "../core/Controller.h"
#include "Object2D.h"


using namespace std;

namespace XOR {

/**
 * Used to create 2D text(can not change z-position, always 0)
 * This uses an underlying bitmap font, which restricts some of its functionality
 * Although it may seem weird, you need to specify the dimensions of the current
 * window. The string coordinates positions are then relative to those dimensions.
 * This is necessary because the string is rendered in a 2D orthographic projection,
 * instead of the 3D Projection. If you want exact screen coordinates, get them from
 * the view object (Controller.getView()).
 *
 * @author John Magnotti
 */
class String2D : public Object2D
{

public:

	/**
	 * Explicit Constructor.
	 *
	 * Note that this doesn't set the position, so it is more for status 
     * messages. The text will be displayed in the upper left region.
	 */
	String2D(char*);


    /**
     * Explicit COnstructor.
     * This constructor is the most fun, as it will use your coordinates as the 
     * position of the string and figure out the window coordinates for you.
     */
    String2D(char *, int, int, const float [3]); 

    
    /**
	 * Explicit Constructor
	 * This is the more recommended way to draw strings. 
	 */
	String2D(char*, int, int);


	/**
	 * Explicit Constructor
	 */
	//String2D(char*, Dimension2D*, Point2D*);


    /**
     * Returns the text of the Strin2D
     */
    char * getText();


    /**
	 * Takes care of rendering the string
	 */
    void renderObject(void);


	/** 
	 * Sets the color of the text.
	 */
    void setColor(const float color[3]);

    /**
     * Sets the display text
     */
    void setText(char*);


    /**
     * Sets the font to use for rendering.
     * At some point using TTF would be nice.
     */
    void setFont(BitmapFontType font);

    void decreaseFontSize();
    void increaseFontSize();


	Dimension2D * getDimension();

	Vector2D * getBaseVector();


private:

	/**
	 * Set the string attributes
	 */
	void build(char * string, int xpos, int ypos, const float color [3]);

	char *			_text;
	int				_xpos, _ypos;
    float           _color[3];

    BitmapFontType * _font;

};

}

#endif          //STRING2D_H

