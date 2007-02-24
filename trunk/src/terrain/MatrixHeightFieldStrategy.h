#ifndef MATRIXHEIGHTFIELDSTRATEGY_H
#define MATRIXHEIGHTFIELDSTRATEGY_H

#include "HeightFieldStrategy.h"

namespace XOR {

/**
 * A strategy that builds a simple matrix-based heightfield
 */
class MatrixHeightFieldStrategy : public HeightFieldStrategy
{
	public:
		
		/**
		 * Default constructor
		 */
		MatrixHeightFieldStrategy(double ** data, int width, int height);

		/**
		 * Returns a function-based heightfield
		 */
		void build(HeightField *target);

	private:

		double ** _matrix;
		int _width, _height;
};

}

#endif		// MATRIXHEIGHTFIELDSTRATEGY_H

