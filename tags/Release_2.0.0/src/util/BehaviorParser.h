#ifndef BEHAVIORPARSER_H
#define BEHAVIORPARSER_H

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "../transform/TransformFactory.h"


namespace XOR {

using namespace std;


/**
 * This is an all-purpose parser for .behavior files.
 * all models can use this class to read in behaviors
 */
class BehaviorParser
{

public:

    /*
     * Returns an instance of the behavior parser
     */
	static BehaviorParser *	GetInstance(char* fileName);

    /**
     * This is the method that does the parsing.
     * Returns a collection of transform objects that represent the parsed file
     */
	vector<Transform*>		parse();
	

protected:

	BehaviorParser();


private:

	static BehaviorParser * _behaviorParser;
	static char *			_pathToFile;
	
};

}

#endif			// BEHAVIORPARSER_H

