#ifndef MUSEUMLAYOUTFACTORY_H
#define MUSEUMLAYOUTFACTORY_H


#include "MuseumLayout.h"


/**
 * Used to create layouts by name
 */
class MuseumLayoutFactory
{

public:

	static MuseumLayout * CreateMuseumLayout(String);

};


#endif			// MUSEUMLAYOUTFACTORY_H
