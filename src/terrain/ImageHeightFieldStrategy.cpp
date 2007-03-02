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

	if (bypp == 4 && bpp == 32)
	{
		unsigned char *p = (unsigned char*)(surf->pixels);
		unsigned int pr,pg,pb,pa;

		target->resizeField(height,width);

		for (r = 0; r < height; r++)
		{
		   for (c = 0; c < width; c++)
		   {
			   pr = (*p++);
			   pg = (*p++);
			   pb = (*p++);
			   pa = (*p++);

			   //cout << "hf[" << r << "][" << c << "]=" << (pr+pg+pb)/3 << endl;

		       // set height to average of RGB colors
			   target->setHeight(r,c,(pr+pg+pb)/3);
		   }
		}

		target->refreshQuads();
	}

	delete surf;
}

}
