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

	cout << "bytes per pixel: " << surf->format->BytesPerPixel << endl;

	int width = surf->w;
	int height = surf->h;
	char *p = (char*)(surf->pixels);

	target->resizeField(height,width);

	for (r = 0; r < height; r++)
	{
		for (c = 0; c < width; c++)
		{
			// function
			target->setHeight(r,c,*(p));
			p++;
		}
	}

	target->refreshQuads();
}

}
