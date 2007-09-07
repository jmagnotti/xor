#ifndef HIDABLERENDERABLE_H
#define HIDABLERENDERABLE_H

#include "../../../xor.h"

using namespace XOR;

/**
 * This project was developed for the Virtual Environment Laboratory at
 * Auburn University.
 *
 *
 * @author John Magnotti (john.magnotti@auburn.edu)
 * @supervisor Jeffrey Katz (katzjf@auburn.edu)
 *
 * @version 1.0
 */
class HidableRenderable : public Object2D
{
public:
	HidableRenderable (Renderable * renderable);

	void renderObject();

	void setVisible(bool visible);

	Dimension2D * getDimension() {}
	Vector2D * getBaseVector() {}

private:

	Renderable * _renderable;
	bool _show;
};

#endif			// HIDABLERENDERABLE_H

