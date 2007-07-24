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
	_paint = new Paint(Color::DARK_KHAKI, Color::BLACK, Paint::HEIGHT_BASED);
}


/**
 * Render the terrain
 */
void HeightField::renderObject(void)
{
	if (_quads == NULL) return;

	int r, c;
	for (r = 0; r < _rows-1; r++) {
		for (c = 0; c < _cols-1; c++) {
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
	_heights = new float * [rows];

	for (y = 0; y < rows; y++)
		_heights[y] = new float[cols];
}


/*
 * get height
 */
float HeightField::getHeight(int row, int col)
{
	return _heights[row][col];
}


/*
 * get normalized height
 */
float HeightField::getNormalHeight(int row, int col)
{
	return ((_heights[row][col] - _min) / (_max-_min)) * _heightScale;
}

/*
 * set height
 */
void HeightField::setHeight(int row, int col, float height)
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
void HeightField::setHeightScale(float factor)
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
    float pts[4];//,p1,p2,p3; 
    float min, max;

    PointScale * ps   = new PointScale(0,1,1);

    TextureScale * ts = new TextureScale(new Vector2D(0.0f, 0.0f), 
            new Dimension2D(_rows, _cols), TextureScale::X_AND_Z,
            TextureScale::STRETCHED);

    float scale = _heightScale;
	int r, c;

	_quads = new Quadrilateral3D ** [_rows-1];
	for (r = 0; r < _rows-1; r++) {
		_quads[r] = new Quadrilateral3D * [_cols-1];

		for (c = 0; c < _cols-1; c++) {
            _heightScale = 1.0f;

            pts[0] = getNormalHeight(c,r);
            pts[1] = getNormalHeight(c,r+1);
            pts[2] = getNormalHeight(c+1,r+1);
            pts[3] = getNormalHeight(c+1,r);

            ps->setScaleDefault(pts[0]);
            max = min = pts[0];

            for (int i=1; i<4; i++) {
                min = pts[i] < min ? pts[i] : min;
                max = pts[i] > max ? pts[i] : max;
            }

            ps->setSystemBounds(min, max);

            _heightScale = scale;

            pts[0] = getNormalHeight(c,   r);
            pts[1] = getNormalHeight(c,   r+1);
            pts[2] = getNormalHeight(c+1, r+1);
            pts[3] = getNormalHeight(c+1, r);

			_quads[r][c] = new Quadrilateral3D(
                                new Vector3D(r,     pts[0], c),
                                new Vector3D(r+1,   pts[1], c),
                                new Vector3D(r+1,   pts[2], c+1),
                                new Vector3D(r,     pts[3], c+1),
                                _paint, ps, ts);
		}
	}
    //#FIXME mem leak?
    //delete ps;
}


Vector3D * HeightField::getBaseVector()
{
	return new Vector3D(0,0,0);
}


Dimension3D * HeightField::getDimension()
{
	return new Dimension3D(_rows, _heightScale, _cols);
}


void HeightField::setPaint(Paint * paint)
{
	if (_quads == NULL) return;

	int r, c;
	for (r = 0; r < _rows-1; r++) {
		for (c = 0; c < _cols-1; c++) {
			_quads[r][c]->setPaint(paint);
		}
	}
	_paint = paint;
}

}

