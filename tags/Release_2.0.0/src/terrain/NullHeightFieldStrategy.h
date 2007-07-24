#ifndef NULLHEIGHTFIELDSTRATEGY_H
#define NULLHEIGHTFIELDSTRATEGY_H

#include "HeightFieldStrategy.h"

namespace XOR {

/**
 * A null strategy that builds a flat heightfield
 */
class NullHeightFieldStrategy : public HeightFieldStrategy
{
	public:
		
		/**
		 * Default constructor
		 */
		NullHeightFieldStrategy();

		/**
		 * Returns a flat terrain
		 */
		void build(HeightField *target);
};

}

#endif		// NULLHEIGHTFIELDSTRATEGY_H

