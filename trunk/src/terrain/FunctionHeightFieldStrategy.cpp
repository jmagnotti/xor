#include "FunctionHeightFieldStrategy.h"

namespace XOR {

/*
 * default constructor
 */
FunctionHeightFieldStrategy::FunctionHeightFieldStrategy(double xmin, double xmax,
		                                                 double ymin, double ymax,
														 double xres, double yres)
{
	_xMinimum = xmin;
	_xMaximum = xmax;
	_yMinimum = ymin;
	_yMaximum = ymax;
	_xResolution = xres;
	_yResolution = yres;
}


/*
 * build the height field
 */
void FunctionHeightFieldStrategy::build(HeightField *target)
{
	double xrange = _xMaximum - _xMinimum;
	double yrange = _yMaximum - _yMinimum;
	int xsize = (int)(xrange / _xResolution);
	int ysize = (int)(yrange / _yResolution);
	double x, y, z;
	int i, j;

	target->resizeField(ysize,xsize);

	y = _yMinimum;
	for (i = 0; i < ysize; i++)
	{
		x = _xMinimum;
		for (j = 0; j < xsize; j++)
		{
			// function
			z = f(x,y);
			target->setHeight(j,i,z);
			x += _xResolution;
		}
		y += _yResolution;
	}

	target->refreshQuads();
}


/*
 * heightfield function
 */
double FunctionHeightFieldStrategy::f(double x, double y)
{
	return 1-sqrt(x*x+y*y);
}

}
