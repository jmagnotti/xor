#ifndef HEIGHTFIELDFACTORY_H
#define HEIGHTFIELDFACTORY_H

#include "HeightFieldStrategy.h"

namespace XOR {

/**
 * Handles the interaction between heightfields and heightfield
 * strategies for the creation phase
 */
class HeightFieldFactory
{
	public:

		/**
		 * Default constructor
		 */
		HeightFieldFactory();


		/**
		 * Singleton accessor
		 */
		static HeightFieldFactory * GetInstance();


		/**
		 * Create a terrain with a given strategy
		 */
		HeightField * buildHeightField(HeightFieldStrategy * strategy);

	private:

		static HeightFieldFactory * _factory;
};

}

#endif		// HEIGHTFIELDFACTORY_H
