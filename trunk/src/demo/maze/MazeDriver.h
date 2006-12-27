#ifndef MAZEDRIVER_H
#define MAZEDRIVER_H


#include "../../xor.h"

#include "Maze.h"
#include "MazeParser.h"

using namespace XOR;

/**
 * Simple maze driver
 */
class MazeDriver
{

public: 
    MazeDriver();

protected:
    initializeMaze();

    // high level model
    Maze *              _maze;

};


#endif          //MAZEDRIVER_H

