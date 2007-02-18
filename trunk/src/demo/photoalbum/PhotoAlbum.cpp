#include "../../xor.h"
#include <string>
#include "xmlParser/xmlParser.h"

using namespace std;
using namespace XOR;


class PhotoAlbum : public DefaultKeyboardListener, public Object3D,
                   public InterpolationListener
{

public:


	Dimension3D * getDimension() {return NULL;}
	Vector3D * getBaseVector() {return NULL;}
	void renderObject() {render();}
	Controller * ctrl;

	/* 
  	* Constructor
 	*/
	PhotoAlbum()
	{
		ctrl = Controller::GetInstance(InputEventHandlerFactory::GetInstance());

        ctrl->defaultConfiguration();
        //ctrl->removeDefaultKeyboardListener();

        ctrl->getKeyboard()->addListener(this);
		ctrl->getMouse()->setDefaultMouseListener(new DefaultMouseListener());
		
        parseXML();
		spaceFlag = false;
		currentPic = 0;  // select first picture by default
		setCurrentPic(currentPic);
		
        s = new String2D("PHOTO DEMO"); 
        ctrl->setModel(this);

		new FramesPerSecondCounter();
		cout << "Passing control" << endl;

		glDisable(GL_DEPTH_TEST);
        ctrl->run();
	}


    void interpolationComplete()
    {
        //cout << "Interpolation complete" << endl;
    }

	void render()
	{
		draw();
	}

    
    void draw()
    {

        vector<Object3D*>::iterator iter = pics.begin();
        vector<Object3D*>::iterator end = pics.end();

        while (iter != end) { 
            (*iter)->render();
            ++iter;
        }
     
        // we want the string on top of everything else
        s->render();
    }
 

    void handleKey_R()
    {
        ctrl->getViewer()->clear();
    }


    void handleKey_S()
    {
        ctrl->getViewer()->incrementTranslation(
                new Vector3D(0,0,1), new TimedInterpolation(1000, this));
    }

	void handleKey_A()
	{
		ctrl->getViewer()->incrementTranslation(
				new Vector3D(0,0,-1), new TimedInterpolation(1000, this));
	}
	
	/** 
     * When you hit the 0 key, all the pictures are set back to 
	 * the grid configuration
	 */
	void handleKey_0()
	{
        vector<Object3D*>::iterator iter = pics.begin();
        vector<Object3D*>::iterator end  = pics.end();

        int i=0;
        while (iter != end )
        {
            ++i;
            if (i == 9) {
                (*iter)->incrementScalar(new Vector3D(1, 0, 0), new TimedInterpolation(1000, this));
                //(*iter)->setTranslation(new Dimension3D(0, 0, 0), new TimedInterpolation(1000, this));
            }

            ++iter; 
        }

	}

    //-- For all other key presses, the corresponding image (QUAD) is
    // made to go quasi-full screen
	
	void handleKey_3()
	{
        vector<Object3D*>::iterator iter = pics.begin();
        vector<Object3D*>::iterator end  = pics.end();

        int i=0;
        while (iter != end ) {
	    ++i;
            (*iter)->incrementRotation(Transformable::ROLL,		360, new TimedInterpolation(600*i, this));
            (*iter)->incrementRotation(Transformable::THETA,	360, new TimedInterpolation(600*i, this));
            (*iter)->incrementRotation(Transformable::PHI,		360, new TimedInterpolation(600*i, this));

            ++iter; 
        }
    }
    
    void handleKey_4()
    {
        bringToFront(4);           
    }

    void handleKey_5()
    {
        bringToFront(8);
    }


    void handleKey_F5()
    {
    	for(int i = 0; i < 36; i++)
        	pics[i]->clear();

	setCurrentPic(currentPic);
    }


	void handleKey_p()
	{
		ctrl->getViewer()->printDebugInfo();
	}

	void handleKey_a()
	{
		ctrl->getViewer()->incrementRotation(0, -10.0f);
	}

	void handleKey_d()
	{
		ctrl->getViewer()->incrementRotation(0, 10.0f);
	}

	void handleKey_w()
	{
		ctrl->getViewer()->walk(0.15f, new TimedInterpolation(200,NULL));
	}

	void handleKey_s()
	{
		ctrl->getViewer()->walk(-0.15f, new TimedInterpolation(200,NULL));
	}

	void handleKey_q()
	{
		ctrl->getViewer()->incrementRotation(2, 5.0f);
	}

	void handleKey_e()
	{
		ctrl->getViewer()->incrementRotation(2, -5.0f);
	}

	void handleKey_c()
	{
		ctrl->getViewer()->incrementRotation(1, 5.0f);
	}

	void handleKey_z()
	{
		ctrl->getViewer()->incrementRotation(1, -5.0f);
	}

	void handleKey_Down()
	{
		// notice we wont let them move if spacebar is toggled
		if(currentPic - 1 >= 0 && !spaceFlag) 
		{
			setCurrentPic(currentPic - 1);
		}
	}

	void handleKey_Up()
	{
		if(currentPic + 1 < numOfPics && !spaceFlag)
		{
			setCurrentPic(currentPic + 1);
		}
	}
	/**
	 * This function only works as-is with rows of 6 pics
	 */
	void handleKey_Left()
	{
		if((currentPic - 6) >= 0 && !spaceFlag)
		{
			setCurrentPic(currentPic - 6);
		}
	}

	/**
	 * This function also only works as-is with rows of 6 pics
	 */
	void handleKey_Right()
	{
		if((currentPic + 6) < numOfPics && !spaceFlag)
		{
			setCurrentPic(currentPic + 6);
		}
	}
	/*
	 * Spacebar will bring a picture to the front
	 */
	void handleKey_Space()
	{
		if(spaceFlag) // if we're in view mode (hit space)
		{
			pics[currentPic]->clear();
			// okay now we have to make the pic look selected again
			setCurrentPic(currentPic);
			spaceFlag = false;  // toggle flag
		}	
		else
		{
			bringToFront(currentPic);
			spaceFlag = true;
		}
	}
	


    void bringToFront(int index)
    {
        // grab x and y from the picture in question
        double x;   // original x position
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
	   	revertPic(index);
	   	
        pics[index]->setScalar(new Vector3D(6, 6, 1), new TimedInterpolation(300, this));
        pics[index]->setTranslation(new Vector3D(newXshift, newYshift, .1), new TimedInterpolation(300, this));
        pics[index]->incrementRotation(Transformable::ROLL,		360, new TimedInterpolation(600, this));
        pics[index]->incrementRotation(Transformable::THETA,	360, new TimedInterpolation(600, this));
        pics[index]->incrementRotation(Transformable::PHI,		360, new TimedInterpolation(600, this));
    }


	void handleKey_7()
	{
		pics[currentPic]->incrementRotation(Transformable::THETA, 90, new TimedInterpolation(1000, this));
	}
    
protected:

	/**
	 * setCurrentPic()  picture changes the pictures on the main display
	 */
	void setCurrentPic(int index)
	{
		// scale down previous picture
		if(currentPic != index) // didn't actually change
		{
			revertPic(currentPic);
		}
		// change the current picture
		currentPic = index;	
		// scale up
        pics[currentPic]->incrementScalar(new Vector3D(.2, .2, .2), new TimedInterpolation(300, this));
	}

	/*
	 *
	 */
	void revertPic(int index)
	{		
		pics[index]->incrementScalar(new Vector3D(-.2,-.2,-.2), new TimedInterpolation(300,this));
	}
	
private:
    
    vector<Object3D*> pics; 
	RectangularPrism *a,*b,*c;
    String2D * s;
    int currentPic;  // the index of the currently selected pic    
    int numOfPics;   // the actual number of pics (not highest index)
	bool spaceFlag;  // are we in view mode? 
	
	void parseXML()
	{
		XMLNode xDemoNode  = XMLNode::openFileHelper("ComputerGiants/ComputerGiants.xml", "demo");
		XMLNode xAlbumNode = xDemoNode.getChildNode("albums").getChildNode("album");
		
		
		int numCubes; // number of cubes we'll need to create

		numCubes = 0;
		// get the number of cube sub objects (height * width)

		// this doesn't actually work because getAttribute returns character arrays
		/*if(xAlbumNode.getAttribute("width") * xAlbumNode.getAttribute("height") == xAlbumNode.nChildNode("cube")) 
		{
			numCubes = xAlbumNode.nChildNode("cube");
		}*/

		numCubes = xAlbumNode.nChildNode("cube");

		int cubeIterator = 0; // the XML library uses this to iterate through child nodes of the same type
		//-------------------------------------------------------------------------------------------------	
        TextureFactory * factory = TextureFactory::GetInstance();

		float squareDiameter = .20;
		float z = 0;
		float offset = .01;

		string fileNames[numCubes]; 
		
		for(int i = 0; i < numCubes; i++)
		{
			int faceIterator = 0;
			int faceCount = 0;

			XMLNode xCubeNode = xAlbumNode.getChildNode("cube", &cubeIterator);
			cout << "Parsing cube " << i + 1 << "..." << endl;
			
			faceCount = xCubeNode.nChildNode("face");
			// loop through all of the faces
			for(int j = 0; j < faceCount; j++)
			{
				XMLNode xFaceNode = xCubeNode.getChildNode("face", &faceIterator);
				cout << "Parsing face " << j + 1 << " on cube " << i + 1 << endl;
				cout << "Filename: " << xFaceNode.getAttribute("image") << endl;
				if(j == 0)
				{
					fileNames[i] = xFaceNode.getAttribute("image");
				}
			
			
			}

		}
		

		for(double i = -3; i < 3; i++)
		{
			for(double j = -3; j < 3; j++)
			{
			
                		cout << "Adding square " << numOfPics << " at: " << i * squareDiameter + offset*i<< ", " 
					<< j * squareDiameter + offset*j<< ", " << z << endl;
				
				pics.push_back(new CompiledObject3D(new RectangularPrism( 
						new Vector3D(i*squareDiameter + offset*i, j*squareDiameter + offset*j, z),
						squareDiameter, squareDiameter, squareDiameter,
						new Paint(Color::WHITE, Paint::HEIGHT_BASED, 
						factory->createTexture(fileNames[numOfPics].c_str())))));
				numOfPics++;  // keep track of number of pics
			}
		}
	}
};	

	
/**
 *  Tester Main
 */
int main(int argc, char **argv)
{
	PhotoAlbum * demo = new PhotoAlbum(); 
    return 0;
}

