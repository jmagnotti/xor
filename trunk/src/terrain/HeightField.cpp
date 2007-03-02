#include <cfloat>

#include "HeightField.h"


namespace XOR {

/**
 * Explicit Constructor
 */
HeightField::HeightField()
{
	_rows = 0;
	_cols = 0;
	_min = FLT_MAX;
	_max = FLT_MIN;
	_heights = NULL;
	_quads = NULL;
	_heightScale = 1.0;
}


/**
 * Render the terrain
 */
void HeightField::renderObject(void)
{
	if (_quads == NULL) return;

	int r, c;
	for (r = 0; r < _rows-1; r++)
	{
		for (c = 0; c < _cols-1; c++)
		{
			_quads[r][c]->render();
		}
	}
}


/*
 * change field size
 */
void HeightField::resizeField(int rows, int cols)
{
	// TODO: clean old memory
	
	int y;
	_rows = rows;
	_cols = cols;
	_heights = new double * [rows];
	for (y = 0; y < rows; y++)
	{
		_heights[y] = new double[cols];
	}
}


/*
 * get height
 */
double HeightField::getHeight(int row, int col)
{
	return _heights[row][col];
}


/*
 * get normalized height
 */
double HeightField::getNormalHeight(int row, int col)
{
	return ((_heights[row][col] - _min) / (_max-_min)) * _heightScale;
}

/*
 * set height
 */
void HeightField::setHeight(int row, int col, double height)
{
	_heights[row][col] = height;

	if (height > _max)
		_max = height;
	else if (height < _min)
		_min = height;
}


/*
 * change height field scale
 */
void HeightField::setHeightScale(double factor)
{
	_heightScale = factor;
	refreshQuads();
}


/*
 * refresh quads
 */
void HeightField::refreshQuads()
{
	// TODO: clean old memory
	
	int r, c;

	_quads = new Quadrilateral3D ** [_rows-1];
	for (r = 0; r < _rows-1; r++)
	{
		_quads[r] = new Quadrilateral3D * [_cols-1];
		for (c = 0; c < _cols-1; c++)
		{
			_quads[r][c] = new Quadrilateral3D(
					new Vector3D(r,getNormalHeight(c,r),c),
					new Vector3D(r+1,getNormalHeight(c,r+1),c),
					new Vector3D(r+1,getNormalHeight(c+1,r+1),c+1),
					new Vector3D(r,getNormalHeight(c+1,r),c+1),
					new Paint(Color::BLACK, 
						Color::DARK_KHAKI,
						Paint::HEIGHT_BASED));
		}
	}

}


Vector3D * HeightField::getBaseVector()
{
	return new Vector3D(0,0,0);
}


Dimension3D * HeightField::getDimension()
{
	return new Dimension3D(_cols,_rows,1);
}


}

