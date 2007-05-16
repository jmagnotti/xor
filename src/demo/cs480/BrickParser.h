#ifndef MAZE_PARSER_H
#define MAZE_PARSER_H

#include <map>
#include <fstream>
#include <string>

#include "../../xor.h"
#include "BrickCollection.h"
#include "Brick.h"
#include "Ball.h"
#include "BreakableBrick.h"

using namespace std;
using namespace XOR;

/**
 * This should use the singleton pattern.
 * Parses maze files. The format: 0=path 1=wall
 */
class BrickParser
{

public:

	/**
	 * Destroys the maze
	 */
	virtual ~BrickParser()
    {}
	

	/**
	 * Returns an instance of a maze parser
	 */
	static BrickParser * GetInstance(char*);


	/**
	 * Parses the maze file
	 */
	BrickCollection * parse(Ball * ball);


protected:

	static char * brickFile;

	/**
	 * Constructors
	 */
	BrickParser(char * pathToFile);
BrickParser(void);


private:

	static BrickParser * _brickParser;

};


#endif		//MAZE_PARSER_H
