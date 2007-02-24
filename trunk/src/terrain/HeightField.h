#ifndef HEIGHTFIELD_H
#define HEIGHTFIELD_H


#include "../shape/Object3D.h"
#include "../geometry/Vector3D.h"
#include "../shape/Quadrilateral3D.h"
#include "../texture/TextureFactory.h"


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
	double getHeight(int row, int col);


	/**
	 * Gets normalized (0..1) height at a particular location
	 */
	double getNormalHeight(int row, int col);


	/**
	 * Change the height at a particular location
	 */
	void setHeight(int row, int col, double height);


	/**
	 * Change the scale factor for the height field
	 */
	void setHeightScale(double factor);


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

protected:


	int						_cols;
	int						_rows;
	double **				_heights;
	Quadrilateral3D ***		_quads;
	double					_min;
	double					_max;
	double					_heightScale;

};

}

#endif			// HEIGHTFIELD_H

