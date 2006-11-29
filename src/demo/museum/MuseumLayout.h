#ifndef MUSEUMLAYOUT_H
#define MUSEUMLAYOUT_H


#include "Museum.h"

/**
 * Abstract parent for layouts
 */
class MuseumLayout
{

public:

	virtual void PerformLayout(Museum *);

}

#endif			// MUSEUMLAYOUT_H
