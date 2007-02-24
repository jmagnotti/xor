#ifndef IMAGEHEIGHTFIELDSTRATEGY_H
#define IMAGEHEIGHTFIELDSTRATEGY_H

#include "HeightFieldStrategy.h"

namespace XOR {

/**
 * A strategy that builds a simple image-based heightfield
 */
class ImageHeightFieldStrategy : public HeightFieldStrategy
{
	public:
		
		/**
		 * Default constructor
		 */
		ImageHeightFieldStrategy(char *path);

		/**
		 * Returns a function-based heightfield
		 */
		void build(HeightField *target);

	private:

		char *_filename;
};

}

#endif		// IMAGEHEIGHTFIELDSTRATEGY_H

