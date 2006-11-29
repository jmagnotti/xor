#ifndef MAZE_PARSER_H
#define MAZE_PARSER_H


#include <fstream>
#include <string>

#include "../../gor.h"

#include "Maze.h"


using namespace std;

/**
 * This should use the singleton pattern.
 * Parses maze files. The format: 0=path 1=wall
 */
class MazeParser
{

public:

	/**
	 * Destroys the maze
	 */
	virtual ~MazeParser()
    {}
	

	/**
	 * Returns an instance of a maze parser
	 */
	static MazeParser* GetInstance(char*);


	/**
	 * Parses the maze file
	 */
	Maze * parse(void);


protected:

	static char * mazeFile;

	/**
	 * Constructors
	 */
	MazeParser(char * pathToFile);
	MazeParser(void);


private:

	static MazeParser * _mazeParser;

};


#endif		//MAZE_PARSER_H
