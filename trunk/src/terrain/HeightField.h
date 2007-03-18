#ifndef HEIGHTFIELD_H
#define HEIGHTFIELD_H


#include "../shape/Object3D.h"
#include "../shape/Quadrilateral3D.h"

#include "../geometry/Vector3D.h"
#include "../geometry/Vector2D.h"
#include "../geometry/Dimension2D.h"
#include "../geometry/Dimension3D.h"

#include "../util/PointScale.h"

#include "../paint/Paint.h"
#include "../paint/Color.h"

#include "../texture/TextureScale.h"


namespace XOR {

/**
 * This class represents a heightfield object. It is basically a 2D array of
 * points. More functionality should come later, like putting objects "on" the
 * terrain.
 * **NOT COMPLETE**
 */
class HeightField : public Object3D
{

public:

	/**
	 * Explicit Constructor
	 */
	HeightField();


	/**
	 * Change the size of the heightfield
	 */
	void resizeField(int rows, int cols);


	/**
	 * Re-generate the quads from the heights
	 */
	void refreshQuads();
	

	/**
	 * Get the height at a particular location
	 */
	float getHeight(int row, int col);


	/**
	 * Gets normalized (0..1) height at a particular location
	 */
	float getNormalHeight(int row, int col);


	/**
	 * Change the height at a particular location
	 */
	void setHeight(int row, int col, float height);


	/**
	 * Change the scale factor for the height field
	 */
	void setHeightScale(float factor);


	/**
	 * Render the terrain
	 */
	void renderObject();


	/**
	 * Returns lower-left coordinates of heightfield
	 */
	Vector3D * getBaseVector();


	/**
	 * Returns size of heightfield
	 */
	Dimension3D * getDimension();


	/**
	 * Set the paint object for the heightfield
	 */
	void setPaint(Paint * paint);


protected:

	Paint					* _paint;

	int						_cols;
	int						_rows;
	float **				_heights;
	Quadrilateral3D ***		_quads;
	float					_min;
	float					_max;
	float					_heightScale;

};

}

#endif			// HEIGHTFIELD_H

