#include "../../xor.h"
//#include <OPENGL/glpng.h>

using namespace std;
using namespace XOR;


class PhotoAlbum : public DefaultKeyboardListener, public Renderable, 
                   public InterpolationListener
{

public:

   /* 
  	* Constructor
 	*/
	PhotoAlbum()
	{
        Controller * ctrl =
            Controller::GetInstance(LocalEventHandlerFactory::GetInstance());

        ctrl->defaultConfiguration();
        ctrl->removeDefaultKeyboardListener();

        ctrl->getKeyboard()->addListener(this);

        //ctrl->getViewer()->setTranslation(new Dimension3D(5,5,5), new
                //TimedInterpolation(3000, this));

        //ctrl->getViewer()->setFocalPoint(new Dimension3D(0,0,0));
        ctrl->getViewer()->incrementTranslation(
				new Dimension3D(0,0,2), new TimedInterpolation(3000, this));

        loadPics();
		
		spaceFlag = false;
		currentPic = 0;  // select first picture by default
		setCurrentPic(currentPic);
		
        s = new String2D("PHOTO DEMO"); 
        ctrl->setModel(this);

        cout << "Passing control" << endl;
        ctrl->run();
	}


    void interpolationComplete()
    {
        //cout << "Interpolation complete" << endl;
    }

    
    void render()
    {
        vector<RectangularPrism*>::iterator iter = pics.begin();
        vector<RectangularPrism*>::iterator end = pics.end();

        while (iter != end) { 
            (*iter)->render();
            ++iter;
        }
     
        // we want the string on top of everything else
        s->render();
    }
 

    void handleKey_R()
    {
        Controller::GetInstance()->getViewer()->clear();
    }


    void handleKey_S()
    {
        Controller::GetInstance()->getViewer()->incrementTranslation(
                new Dimension3D(0,0,1), new TimedInterpolation(1000, this));
    }

	void handleKey_A()
	{
		Controller::GetInstance()->getViewer()->incrementTranslation(
				new Dimension3D(0,0,-1), new TimedInterpolation(1000, this));
	}
	
	/** 
     * When you hit the 0 key, all the pictures are set back to 
	 * the grid configuration
	 */
	void handleKey_0()
	{
        vector<RectangularPrism*>::iterator iter = pics.begin();
        vector<RectangularPrism*>::iterator end  = pics.end();

        int i=0;
        while (iter != end )
        {
            ++i;
            if (i == 9) {
                (*iter)->incrementScalar(new Dimension3D(1, 0, 0), new TimedInterpolation(1000, this));
                //(*iter)->setTranslation(new Dimension3D(0, 0, 0), new TimedInterpolation(1000, this));
            }

            ++iter; 
        }

	}

    //-- For all other key presses, the corresponding image (QUAD) is
    // made to go quasi-full screen
	
	void handleKey_3()
	{
        vector<RectangularPrism*>::iterator iter = pics.begin();
        vector<RectangularPrism*>::iterator end  = pics.end();

        int i=0;
        while (iter != end ) {
	    ++i;
            (*iter)->incrementRotation(Positionable::ROLL,	360, new TimedInterpolation(600*i, this));
            (*iter)->incrementRotation(Positionable::THETA,	360, new TimedInterpolation(600*i, this));
            (*iter)->incrementRotation(Positionable::PHI,	360, new TimedInterpolation(600*i, this));

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
        pics[4]->clear();
    }


	void handleKey_p()
	{
		Controller::GetInstance()->getViewer()->printDebugInfo();
	}

	void handleKey_a()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(0, -10.0f);
	}

	void handleKey_d()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(0, 10.0f);
	}

	void handleKey_w()
	{
		Controller::GetInstance()->getViewer()->walk(0.15f, new TimedInterpolation(200,NULL));
	}

	void handleKey_s()
	{
		Controller::GetInstance()->getViewer()->walk(-0.15f, new TimedInterpolation(200,NULL));
	}

	void handleKey_q()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(2, 5.0f);
	}

	void handleKey_e()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(2, -5.0f);
	}

	void handleKey_c()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(1, 5.0f);
	}

	void handleKey_z()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(1, -5.0f);
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
        /*
        // grab x and y from the picture in question
        double x;   // original x position
        double y;
        Point3D * currentPoint;
        
        currentPoint = pics[index].getRegistrationPoint();
       
        x = currentPoint->getX();
        y = currentPoint->getY();
        */
        //need to move about .53 in the x and about -0.3 in the y

        // need scale the pic back to it's original form before messing with it
	   	revertPic(index);
	   	
        //pics[index]->setScalar(new Dimension3D(3, 3, 1), new TimedInterpolation(300, this));
        pics[index]->setTranslation(new Dimension3D(.2, -.3, .1), new TimedInterpolation(300, this));
        pics[index]->incrementRotation(Positionable::ROLL,	360, new TimedInterpolation(600, this));
        pics[index]->incrementRotation(Positionable::THETA,	360, new TimedInterpolation(600, this));
        pics[index]->incrementRotation(Positionable::PHI,	360, new TimedInterpolation(600, this));
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
        pics[currentPic]->incrementScalar(new Dimension3D(.2, .2, .2), new TimedInterpolation(300, this));
	}

	/*
	 *
	 */
	void revertPic(int index)
	{		
		pics[index]->incrementScalar(new Dimension3D(-.2,-.2,-.2), new TimedInterpolation(300,this));
	}
	
	void loadPics()
	{
        
        TextureFactory * factory = TextureFactory::GetInstance();

		float squareDiameter = .20;
		float z = 0;
		float offset = .01;
				
		int ii=0;
		for(double i = -3; i<3; i++) {
	   		for (double j = -3; j<3; j++) {
				numOfPics++;  // keep track of number of pics
                cout << "Adding square " << ii << " at: " << i * squareDiameter + offset*i<< ", " << j * squareDiameter + offset*j<< ", " << z << endl;
			   	pics.push_back(new RectangularPrism(
					new Point3D(i*squareDiameter + offset*i, j*squareDiameter + offset*j, z),
					squareDiameter, squareDiameter, squareDiameter,
					new Paint(Color::RED, Paint::HEIGHT_BASED, factory->createTexture("monkey.png"))
                        //.1,.1f*(i+2), .1f*(i+3), Paint::HEIGHT_BASED)
				));
                /*```pics.push_back(new RectangularPrism(
                            new Point3D(i*squareDiameter + offset*i, j*squareDiameter + offset*j, z),
                            squareDiameter, squareDiameter, squareDiameter,
                            new Paint(loadPic(NULL))
                            ));*/
                ++ii;
			}
		}
	}

private:
    
    vector<RectangularPrism*> pics; RectangularPrism *a,*b,*c;
    String2D * s;
    int currentPic;  // the index of the currently selected pic    
    int numOfPics;   // the actual number of pics (not highest index)
	bool spaceFlag;  // are we in view mode? 
	
	//vector<TimedInterpolation*> _interpolation
    /*  
    GLuint loadPic(char * filename)
    {
        GLuint texture;
        pngInfo info;
        //glEnable(GL_TEXTURE_2D); 
        texture = pngBind("babytux.png", PNG_NOMIPMAP, PNG_ALPHA, &info, GL_REPEAT, GL_NEAREST, GL_NEAREST);
        
    }
   */ 
    
};	

	
/**
 *  Tester Main
 */
int main(int argc, char **argv)
{
	PhotoAlbum * demo = new PhotoAlbum(); 
    return 0;
}

