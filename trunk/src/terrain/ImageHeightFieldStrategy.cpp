#include "ImageHeightFieldStrategy.h"

namespace XOR {

/*
 * default constructor
 */
ImageHeightFieldStrategy::ImageHeightFieldStrategy(char *path)
{
	_filename = path;
}


/*
 * build the height field
 */
void ImageHeightFieldStrategy::build(HeightField *target)
{
	int r, c;

	SDL_Surface *surf = IMG_Load(_filename);

	int bypp = (int)(surf->format->BytesPerPixel);
	int bpp = (int)(surf->format->BitsPerPixel);
	int width = surf->w;
	int height = surf->h;

	cout << "bytes per pixel: " << bypp << endl;
	cout << "bits per pixel: " << bpp << endl;
	cout << "width: " << width << endl;
	cout << "height: " << height << endl;

	unsigned char *p = (unsigned char*)(surf->pixels);
	unsigned int pr,pg,pb,pa;

	if ((bypp == 4 && bpp == 32) ||		// 32-bit color (8-bit RGB w/ alpha channel)
	    (bypp == 3 && bpp == 24)) {		// 24-bit color (8-bit RGB only)
		target->resizeField(height,width);
		for (r = 0; r < height; r++) {
		   for (c = 0; c < width; c++) {
			   // red, green, blue
			   pr = (*p++); pg = (*p++); pb = (*p++);
			   // alpha (if present)
			   if (bypp == 4)
				   pa = (*p++);
		       // set height to average of RGB colors
			   target->setHeight(r,c,(pr+pg+pb)/3);
		   }
		}
		target->refreshQuads();
	}

	delete surf;
}

}
