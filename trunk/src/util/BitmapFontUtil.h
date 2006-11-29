#ifndef BITMAPFONTUTIL_H
#define BITMAPFONTUTIL_H


#include "BitmapFontConstants.h"


namespace XOR {


/**
 *	Name: bitmap_fonts.h	|| BitmapFontUtil.h
 *	Author: John Fay		|| modification, cleaning, "class"ification by magnotti 
 *	Last Modified: 01/26/05
 *	Description: Data and utility functions for rendering bitmap based fonts. 
 *	This is a modified version of the bitmap based rendering 
 *	system from the open source Freeglut project.
 *	http://freeglut.sourceforge.net/
 */
class BitmapFontUtil
{

public:

	/**
	 * Call this function to push the appropriate font rendering state. 
	 * Call endRenderText to pop the attributes.
	 */
	static void beginRenderText(int windowWidth, int windowHeight);


	/**
	 * Call this function to pop the font rendering state. The call to
	 * beginRenderText must come before this one.
	 */
	static void endRenderText( void );


	/**
	 * Matches a BitmapFontType with a BitmapFontData structure pointer.
	 */
	static const BitmapFontData* getBitmapFontDataByType( BitmapFontType font );


	/**
	 * This function must be called in between a call to 
	 * beginRenderText and endRenderText.
	 */
	static void renderText(float x, float y,
							BitmapFontType fontType, char *string );

};

}

#endif			// BITMAPFONTUTIL_H
