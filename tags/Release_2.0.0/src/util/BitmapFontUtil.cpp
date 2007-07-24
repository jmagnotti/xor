#include "BitmapFontUtil.h"

namespace XOR {

/* 
 * Return a reference to the proper font
 */
const BitmapFontData * BitmapFontUtil::getBitmapFontDataByType
    (BitmapFontType * font)
{
	if(*font == BITMAP_FONT_TYPE_8_BY_13)
		return &FontFixed8x13;
	if(*font == BITMAP_FONT_TYPE_9_BY_15)
		return &FontFixed9x15;
	if(*font == BITMAP_FONT_TYPE_HELVETICA_10)
		return &FontHelvetica10;
	if(*font == BITMAP_FONT_TYPE_HELVETICA_18)
		return &FontHelvetica18;
	if(*font == BITMAP_FONT_TYPE_TIMES_ROMAN_10)
		return &FontTimesRoman10;
	if(*font == BITMAP_FONT_TYPE_TIMES_ROMAN_24)
		return &FontTimesRoman24;

    // sensible default
    return &FontHelvetica12;

}
	

/*
 * Render the text to the screen
 */
void BitmapFontUtil::renderText(float x, float y, BitmapFontType * fontType,
	char* string)
{
	glRasterPos2f(x,y);

	const BitmapFontData* font = getBitmapFontDataByType( fontType );
	const unsigned char* face;
	char* c = '\0';

	for(c = string; *c != '\0'; ++c) {
		// Find the character face that we want to draw.
		face = font->Characters[*c-1];

		glBitmap( face[0], font->Height,    // The bitmap's width and height
			font->xorig, font->yorig,       // The origin in the font glyph
			(float)(face[0]), 0.0,          // The raster advance -- inc. x,y
			(face+1) );                     // The packed bitmap data...
	}
}

}

