#include "PhotoAlbum.h"


Dimension3D * PhotoAlbum::getDimension() {new Dimension3D(1,1,1);}

Vector3D * PhotoAlbum::getBaseVector() {new Vector3D(0,0,0);}


/* 
* Constructor
*/
PhotoAlbum::PhotoAlbum()
{
	expectedInterpolations = 0;
	receivedInterpolations = 0;

	numOfPics = 0;
	parseXML();
	
	interpolationManager = new InterpolationManager(this, numOfPics);
	
	unlockKeys();
	currentPic = 0;  // select first picture by default
	setCurrentPic(currentPic);

	pDemo = new String2D("PHOTO DEMO"); 

    //new FramesPerSecondCounter();
}

/**
 * This method is called whenever an interpolation has
 * finished. Useful for unlocking the keys
 */
void PhotoAlbum::interpolationComplete()
{
	receivedInterpolations++;
	cout << "Received Interpolations: \t" << receivedInterpolations <<
		"Expected Interpolations: \t" << expectedInterpolations << 
		endl; // debug

	unlockKeys();
}

void PhotoAlbum::render()
{
	renderObject();
}

void PhotoAlbum::renderObject()
{
	vector<Object3D*>::iterator iter = pics.begin();
	vector<Object3D*>::iterator end = pics.end();

	while (iter != end) { 
		(*iter)->render();
		++iter;
	}
 
	// we want the string on top of everything else
	pDemo->render();
}

void PhotoAlbum::bringToFront(int index)
{
	// grab x and y from the picture in question
 	// original x position
	double x;
	double y;
	
	double newXshift;
	double newYshift;

	Vector3D * currentPoint;
		
	// Get a copy of the point so we can 
	// extract the x and y values to work on
	currentPoint = pics[index]->getBaseVector();
   
	x = currentPoint->getX();
	y = currentPoint->getY();
	
	// want to shift to the right spot
	newXshift = -0.101 - x;
	newYshift = -0.1 - y;
	//need to move about .53 in the x and about -0.3 in the y

	// need scale the pic back to it's original form before messing with it
	//////unhighlightPic(index);	

	//pics[index]->incrementScalar(new Vector3D(3, 3, 0));
	//pics[index]->setTranslation(new Vector3D(-3,-3, 0), new TimedInterpolation(500, this));

}

/**
 * setCurrentPic()  picture changes the pictures on the main display
 */
void PhotoAlbum::setCurrentPic(int index)
{
	// first ensure that we're allowed to access keyboard
	if(!keyboardLocked) {
		// scale down previous picture
		if(currentPic != index) // didn't actually change
		{
			//unhighlightPic(currentPic);
		}
		// change the current picture
		currentPic = index;	
		
		lockKeys(1); 
		// scale up
		//highlightPic();
		// print out the index of currently highlighted pic
	}
}
/**
 * toggleViewMode() will switch between single photo
 * view mode and multi photo view mode. 
 */
void PhotoAlbum::toggleViewMode()
{
	// if the keyboard is locked // this means we're already in // view
	// mode
	if(keyboardLocked) {

		//pics[currentPic]->clear();  // put pic back
		receivedInterpolations++;   // cheat a little bit
		unlockKeys();
		setCurrentPic(currentPic);  // put it in highlighted state
	}
	else  // otherwise enter view mode
	{
		bringToFront(currentPic);
		//lockKeys(2);
	}
}

/**
 * the moveSelected<direction> series
 * is intended for use with a keyboard
 *
 * it selects photos in an appropriate direction
 */
void PhotoAlbum::moveSelectedUp()
{	
	if(currentPic + 1 < numOfPics && !keyboardLocked)
		setCurrentPic(currentPic + 1);
}

void PhotoAlbum::moveSelectedDown()
{
	if(currentPic - 1 >= 0 && !keyboardLocked) 
		setCurrentPic(currentPic - 1);
	else if(currentPic - 1 < 0 && !keyboardLocked)
		setCurrentPic(numOfPics + (currentPic - 1));
}

void PhotoAlbum::moveSelectedRight()
{
	// debug
	// cout << "currentpic: " << currentPic << " \tnumOfPics:" << numOfPics << endl;
	if((currentPic + 6) < numOfPics && !keyboardLocked) {
		setCurrentPic(currentPic + 6);
	}
	// numOfPics is the actual number of pics (not counting from zero)
	// so to see if we're at the last pic we must add one to currentPic
	else if(currentPic + 1 == numOfPics && !keyboardLocked) // at top right
	{
		setCurrentPic(0); // go back to beginning
	}
	else if((currentPic + 6) >= numOfPics && !keyboardLocked)
	{
		// this will move to the first column and the next row down
		// -30 puts us in the same row, but first column
		// +1 moves up a row
		setCurrentPic(currentPic - 30 + 1);
	}
}

void PhotoAlbum::moveSelectedLeft()
{
	if((currentPic - 6) >= 0 && !keyboardLocked) {
		setCurrentPic(currentPic - 6);
	}
	else if(currentPic == 0 && !keyboardLocked) {
		// at bottom left
		setCurrentPic(35); // go to end 
	}
	else if((currentPic - 6) < 0 && !keyboardLocked) {
		// this will move to the first column and the next row down
		// +30 puts us in the same row, but last column
		// -1 moves down a row
		setCurrentPic(currentPic + 30 - 1);
	}
}
void PhotoAlbum::magnottiTransform()
{
	
	if(!keyboardLocked)
	{
		int numOfInterpolations;
		numOfInterpolations = 0;

		vector<Object3D*>::iterator iter = pics.begin();
		vector<Object3D*>::iterator end  = pics.end();
		int i=0;
		while (iter != end ) {	
			numOfInterpolations += 3;
			TimedInterpolation * tmpInterp;
			tmpInterp = interpolationManager->getInterpolation(i);
            /*
			(*iter)->incrementRotation(Orientation::ROLL, 360, tmpInterp);
			(*iter)->incrementRotation(Orientation::THETA, 360, tmpInterp);
			(*iter)->incrementRotation(Orientation::PHI, 360, tmpInterp);
            */
			++i;
			++iter; 
		}

		lockKeys(numOfInterpolations);
	}
}

void PhotoAlbum::resetAllPhotos()
{
    /*
	for(int i = 0; i < 36; i++)
		pics[i]->clear();
        */

	// we have to bring the current pic back
	// because clear() puts everything in its
	// creation position, not where we want
	// them
	setCurrentPic(currentPic);
}

/*
void PhotoAlbum::highlightPic()
{
	// TODO: replace the object's paint object with an alpha blended colorized one
	// paint stuff
	//	new Paint(Color::WHITE, Paint::HEIGHT_BASED, factory->createTexture(fileNames[numOfPics].c_str())))));
		pics[currentPic]->incrementScalar(new Vector3D(.2, .2, .2), new TimedInterpolation(150, this));
}
*/

    /*
void PhotoAlbum::unhighlightPic(int index)
{
	pics[index]->incrementScalar(new Vector3D(-.2,-.2,-.2), new TimedInterpolation(300,this));
}

    */
/**
 * lockKeys(int) will lock the keyboard until it's
 * reached the expected amount of interpolations
 *
 * @param expectedInterpolations - The number of interpolations
 *			to receive before unlocking
 */
void PhotoAlbum::lockKeys(int expectedInterpolations)
{
	this->expectedInterpolations = expectedInterpolations;
	keyboardLocked = true;//true;
}

/**
 * unlockKeys() will unlock the keyboard if the expected 
 * amount of interpolations has been received.
 */
void PhotoAlbum::unlockKeys()
{
	// once we get the expected amount of interpolations we
	// have to be sure to clear the number of received
	// interpolations, otherwise buggy things happen
	if(receivedInterpolations >= expectedInterpolations)
	{
		receivedInterpolations = 0;
		keyboardLocked = false;
	}
}
void PhotoAlbum::parseXML()
{
	XMLNode xDemoNode  = XMLNode::openFileHelper("ComputerGiants/ComputerGiants.xml", "demo");
	XMLNode xAlbumNode = xDemoNode.getChildNode("albums").getChildNode("album");
	
	int numCubes; // number of cubes we'll need to create
	numCubes = 0;
	// get the number of cube sub objects (height * width)

	numCubes = xAlbumNode.nChildNode("cube");

	int cubeIterator = 0; // the XML library uses this to iterate through child nodes of the same type
	//-------------------------------------------------------------------------------------------------	
	TextureFactory * factory = TextureFactory::GetInstance();

	float squareDiameter = .20;
	float z = 0;
	float offset = .01;

	string fileNames[numCubes]; 
	
	for(int i = 0; i < numCubes; i++) {
		int faceIterator = 0;
		int faceCount = 0;

		XMLNode xCubeNode = xAlbumNode.getChildNode("cube", &cubeIterator);
		//cout << "Parsing cube " << i + 2 << "..." << endl; //debg
		
		faceCount = xCubeNode.nChildNode("face");

		// loop through all of the faces
		for(int j = 0; j < faceCount; j++) {
			XMLNode xFaceNode = xCubeNode.getChildNode("face", &faceIterator);
			if(j == 0) {
				fileNames[i] = xFaceNode.getAttribute("image");
			}
		}
	}
	
	// populate the screen with rectangular prisms
	for(double i = -3; i < 3; i++) {
		for(double j = -3; j < 3; j++) {

			Vector3D * vOff = new Vector3D(i*squareDiameter + offset*i, j*squareDiameter + offset*j, z);

			Cube * c = new Cube( vOff, squareDiameter, new Paint(Color::WHITE, Paint::HEIGHT_BASED, factory->createTexture(fileNames[numOfPics].c_str())));

			//c->setTranslation(vOff);

			pics.push_back(new CompiledObject3D(c));

			numOfPics++;  // keep track of number of pics
		}
	}
}

