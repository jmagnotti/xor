#ifndef STRING2D_H
#define STRING2D_H


#include <string.h>
#include "../util/BitmapFontUtil.h"
#include "../geometry/Dimension2D.h"
#include "../paint/Paint.h"
#include "Renderable.h"
#include "../core/Controller.h"
#include "../core/Viewer.h"



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
 * It is correct to think that the String2D class should not be changing the world
 * projection. At some point this will be refactored into a more appropriate place.
 */
class String2D : public Renderable
{

public:

	/**
	 * Explicit Constructor.
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
	String2D(char*, int, int, int, int);


	/**
	 * Explicit Constructor
	 * This is the same as the above constructor, except it uses a Dimension2D 
     * object to specify size
	 */
	String2D(char*, Dimension2D*, int, int);


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
    void render(void);


	/** 
	 * Set the paint of the object
	 *
	 * This paint SHOULD NOT have a gradient. The underlying
	 * implementation will only use Paint.getColorTo(). Future versions may allow for
	 * a choppy gradient in which each letter is progressively colored, this might be
	 * really resource intensive, and a display list would have to be created, but
	 * that isn't horrible.
	 */
	//void setPaint(Paint*);

    void setColor(const float color[3]);

    /**
     * Sets the display text
     */
    void setText(char*);


protected:

	GLuint			_stringDL;
	char *			_text;
	int				_xpos, _ypos;
    float           _color[3];

	Dimension2D *	_size;
	//Paint *			_paint;

};

}

#endif          //STRING2D_H
