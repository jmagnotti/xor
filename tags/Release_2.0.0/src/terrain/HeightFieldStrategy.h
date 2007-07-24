#ifndef HEIGHTFIELDSTRATEGY_H
#define HEIGHTFIELDSTRATEGY_H

#include "HeightField.h"

namespace XOR {

/**
 * A class that performs operations on the terrain. Should allow for quick swapping of terrain
 * maps
 */
class HeightFieldStrategy
{
	public:
		virtual void build(HeightField *target) {}
};

}

#endif		// HEIGHTFIELDSTRATEGY_H

