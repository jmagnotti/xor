#include "MatrixHeightFieldStrategy.h"

namespace XOR {

/*
 * default constructor
 */
MatrixHeightFieldStrategy::MatrixHeightFieldStrategy(double ** data, int width, int height)
{
	_matrix = data;
	_width = width;
	_height = height;
}


/*
 * build the height field
 */
void MatrixHeightFieldStrategy::build(HeightField *target)
{
	int r, c;

	double *p = (double*)_matrix;

	target->resizeField(_height,_width);

	for (r = 0; r < _height; r++)
	{
		for (c = 0; c < _width; c++)
		{
			target->setHeight(r,c,*(p));
			p++;
		}
	}

	target->refreshQuads();
}

}
