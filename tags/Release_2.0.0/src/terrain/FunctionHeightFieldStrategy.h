#ifndef FUNCTIONHEIGHTFIELDSTRATEGY_H
#define FUNCTIONHEIGHTFIELDSTRATEGY_H

#include "HeightFieldStrategy.h"

namespace XOR {

/**
 * A strategy that builds a simple function-based heightfield
 */
class FunctionHeightFieldStrategy : public HeightFieldStrategy
{
	public:
		
		/**
		 * Default constructor
		 */
		FunctionHeightFieldStrategy(double xmin, double xmax,
				                    double ymin, double ymax,
									double xres, double yres);


		/**
		 * Returns a function-based heightfield
		 */
		void build(HeightField *target);


		/**
		 * Heightfield function
		 */
		virtual double f(double x, double y);

	private:

		double _xMinimum, _xMaximum;
		double _yMinimum, _yMaximum;
		double _xResolution, _yResolution;
};

}

#endif		// FUNCTIONHEIGHTFIELDSTRATEGY_H

