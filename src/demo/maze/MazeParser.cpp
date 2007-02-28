#include "MazeParser.h"

// set initial values for static members
MazeParser * MazeParser::_mazeParser = 0;
char *       MazeParser::mazeFile    = "maze.mz";


/*
 * Protected Constructor
 */
MazeParser::MazeParser()
{}


/*
 * Singleton accessor
 */
MazeParser * MazeParser::GetInstance(char * path)
{
	mazeFile = path;

	if (_mazeParser == NULL)
		_mazeParser = new MazeParser();

	return _mazeParser;
}


/*
 * Parses the maze file
 */
Maze * MazeParser::parse()
{
	Maze * maze = new Maze();
	TextureFactory * tf = TextureFactory::GetInstance();

	//set a paint to be used by the maze
    Paint * p =  new Paint(Color::BLACK, Color::WHITE, Paint::HEIGHT_BASED, tf->createTexture("rustyblue.bmp"));
    //Paint * p =  new Paint(Color::BLACK, Color::SNOW, Paint::HEIGHT_BASED);//, tf->createTexture("greenstone.bmp"));

	//initialize a file stream reader
	ifstream fin(mazeFile);

	if (!fin) {
		// the mazeparser should be a bit more robust, maybe return a default maze
		//maze->addRenderable(new Cube());
	}
	else {
		int size, entry = 0;
		string tempStr = "";
		int points [2][2];

		fin >> size;

		//read in the beginning and ending points
		for(int i = 0; i < 2;i++) {
			fin >> tempStr;		//eat the first word
            for(int j=0;j<2;j++) {
				fin >> points[i][j];
			}
		}

		// note that we are switching 0 and 1, as well as giving Y as default value of 0
		maze->setStartingPoint(new Vector3D(points[0][1]-.5, .5, points[0][0]));
		maze->setFinishingPoint(new Vector3D(points[1][1], 0, points[1][0]));

		// initialize the maze
        for (int row=0; row < size && entry != EOF; row++) {
			for (int column=0; column < size && entry != EOF; column++) {
				fin >> entry;
				if (entry)
					maze->addRenderable(new RectangularPrism(new Vector3D(row, 0.0f, column), 1, entry, 1, p));
			}
        }
	}
	fin.close();

	return maze;
}
