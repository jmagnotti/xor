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
        Controller * ctrl = Controller::GetInstance();

        ctrl->defaultConfiguration();
        ctrl->removeDefaultKeyboardListener();
        //ctrl->getViewer()->incrementTranslation(new Dimension3D(0,1,0), new TimedInterpolation(3000, this));
        //ctrl->getViewer()->incrementTranslation(new Dimension3D(1,0,3), new TimedInterpolation(3000, this));

        loadPics();

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
        
        pics[index]->incrementScalar(new Dimension3D(7, 7, 1), new TimedInterpolation(300, this));
        pics[index]->incrementTranslation(new Dimension3D(.53, -.3,-.1), new TimedInterpolation(300, this));
    }
    
protected:

	/**
	 * setCurrentPic()  picture changes the pictures on the main display
	 */
	void setCurrentPic(int index)
	{}

	void loadPics()
	{
		float squareDiameter = .20;
		float z = 0;
		float offset = .01;
				
		int ii=0;
		for(double i = -3; i<3; i++) {
	   		for (double j = -3; j<3; j++) {
                cout << "Adding square " << ii << " at: " << i * squareDiameter + offset*i<< ", " << j * squareDiameter + offset*j<< ", " << z << endl;
			   	pics.push_back(new RectangularPrism(
					new Point3D(i*squareDiameter + offset*i, j*squareDiameter + offset*j, z),
					squareDiameter, squareDiameter, squareDiameter,
					new Paint(.1,.1f*(i+2), .1f*(i+3), Paint::HEIGHT_BASED)
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

