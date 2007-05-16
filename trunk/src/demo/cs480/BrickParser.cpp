#include "BrickParser.h"

// set initial values for static members
BrickParser * BrickParser::_brickParser = 0;
char *       BrickParser::brickFile    = "bricks.brx";


/*
 * Protected Constructor
 */
BrickParser::BrickParser()
{}


/*
 * Singleton accessor
 */
BrickParser * BrickParser::GetInstance(char * path)
{
	brickFile = path;

	if (_brickParser == NULL)
		_brickParser = new BrickParser();

	return _brickParser;
}


/*
 * Parses the maze file
 */
BrickCollection * BrickParser::parse(Ball * ball)
{
	BrickCollection * bc = new BrickCollection(ball);

	//initialize a file stream reader
	ifstream fin(brickFile);

	if (!fin) {
		// the mazeparser should be a bit more robust, maybe return a default maze
		//maze->addRenderable(new Cube());
		cout << "FAILED to load file" << endl;
	}
	else {
		int rows, cols, entry = 0;
		string tempStr = "";
		
		fin >> tempStr; // "eat" rows
		fin >> rows;    // read  rows
		fin >> tempStr; // "eat" cols
		fin >> cols;    // read  cols

		float offset = 1.0f;
		float y = 0.0f;

		// populate the screen with bricks
		//for(double i = -1 * (rows / 2); i < (rows / 2); i++) {
			//for(double j = -1 * (cols / 2); j < (cols / 2); j++) {
		for(double i=0; i<rows+0; i++) {
			for(double j=0+2; j<cols+2; j++) {
				fin >> entry;
				
				// if we have a brick
				if(entry > 0) {
					Vector3D * vOff = new Vector3D(i + offset*i, y, j + offset*j);

					BreakableBrick * brick = new BreakableBrick(vOff,
							new Dimension3D(1,1,1), 
							new Paint(Color::BLUE, Paint::HEIGHT_BASED));

					//cout << "brick: " << vOff->toString() << endl;
					bc->addBrick(brick);
				}
			}
		}
		fin.close();

		return bc;
	}
}

