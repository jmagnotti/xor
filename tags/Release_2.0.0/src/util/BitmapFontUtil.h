#ifndef BITMAPFONTUTIL_H
#define BITMAPFONTUTIL_H


#include "BitmapFontConstants.h"


namespace XOR {

/**
 *	Name: bitmap_fonts.h	|| BitmapFontUtil.h
 *	Author: John Fay		|| modification, cleaning, "class"ification by magnotti 
 *	Last Modified: 01/26/05 || March 2006
 *	Description: Data and utility functions for rendering bitmap based fonts. 
 *	This is a modified version of the bitmap based rendering 
 *	system from the open source Freeglut project.
 *	http://freeglut.sourceforge.net/
 */
class BitmapFontUtil
{

public:

	/**
	 * Matches a BitmapFontType with a BitmapFontData structure pointer.
	 */
	static const BitmapFontData * getBitmapFontDataByType(
            BitmapFontType * font);


	/**
     * Takes care of actual rendering the bitmaps
	 */
	static void renderText(float x, float y, 
            BitmapFontType * fontType, char * string);

};

}

#endif			// BITMAPFONTUTIL_H

