#ifndef TRANSFORMFACTORY_H
#define TRANSFORMFACTORY_H

#include <string>
#include <vector>

#include "Transform.h"
#include "Rotate.h"
#include "Translate.h"

using namespace std;

namespace XOR {

class TransformFactory
{

public:

	/** 
	 * Creates a transform
	 */
	static	Transform * CreateTransform(string[5]);

	/**
	 * Explicit Constructor
	 * This constructor is to be used only by the XML-to-GOR Tool. 
	 * Use the other constructors for other uses, as they are MUCH more efficeint
	 */
//	static Transform * CreateTransform(String, String, String, String, String);


};

}

#endif			// TRANSFORMFACTORY_H


