#include "NullHeightFieldStrategy.h"

namespace XOR {

/*
 * default constructor
 */
NullHeightFieldStrategy::NullHeightFieldStrategy()
{
}


/*
 * build the height field
 */
void NullHeightFieldStrategy::build(HeightField *target)
{
	int size = 2, r, c;

	target->resizeField(size,size);

	for (r = 0; r < size; r++)
	{
		for (c = 0; c < size; c++)
		{
			target->setHeight(r,c,0);
		}
	}

	target->refreshQuads();
}

}
