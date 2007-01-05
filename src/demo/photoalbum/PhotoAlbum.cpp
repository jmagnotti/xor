#include "../../xor.h"


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

        /*
            a = new RectangularPrism(new Point3D(0,-1,-1), .5f, new Paint(Color::RED, Paint::HEIGHT_BASED));
            b = new RectangularPrism(new Point3D(-1,0,-1), .5f, new Paint(Color::GREEN, Paint::HEIGHT_BASED));
            c = new RectangularPrism(new Point3D(-1,-1,-1), .5f, new Paint(Color::BROWN, Paint::HEIGHT_BASED));
        */

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
        s->render();

        vector<RectangularPrism*>::iterator iter = pics.begin();
        vector<RectangularPrism*>::iterator end = pics.end();

        while (iter != end) { 
            (*iter)->render();
            ++iter;
        }
    }
 

	/**
	 * When you hit the 0 key, all the pictures are set back to 
	 * the grid configuration
	 */
	void PhotoAlbum::handleKey_0()
	{
		//cout << Controller::GetInstance()->getViewer()->getFocalPoint()->toString() << endl;
	}

    //-- For all other key presses, the corresponding image (QUAD) is
    // made to go quasi-full screen
	
	void PhotoAlbum::handleKey_1()
	{ 
        //Controller::GetInstance()->getViewer()->incrementTranslation(new Dimension3D(0,1,0));
    }

	void PhotoAlbum::handleKey_2()
    {
        //Controller::GetInstance()->getViewer()->incrementRotation(Positionable::THETA, 180, _interpolation);
    }
	
	void PhotoAlbum::handleKey_3()
	{
        vector<RectangularPrism*>::iterator iter = pics.begin();
        vector<RectangularPrism*>::iterator end  = pics.end();

        //vector<TimedInterpolation*>::iterator i_iter = _interpolation.begin();
        //vector<TimedInterpolation*>::iterator i_end  = _interpolation.end();

        int i=1;
        while (iter != end ) {
               // && i_iter != i_end
            (*iter)->incrementRotation(Positionable::ROLL, 30, new TimedInterpolation(1000, this));
            (*iter)->incrementRotation(Positionable::THETA, 35, new TimedInterpolation(1000, this));
            (*iter)->incrementRotation(Positionable::PHI, 40, new TimedInterpolation(1000, this));
            //(*iter)->setPaint(new Paint(i*.3, .2, i*.2));
            //(*iter)->incrementTranslation(new Dimension3D(0,.3,0), (*i_iter));
            ++iter; 
          //  ++i_iter;
            ++i;
        }
    }
	
	void PhotoAlbum::handleKey_4()
	{}

	void PhotoAlbum::handleKey_5()
	{}

	void PhotoAlbum::handleKey_6()
	{}

	void PhotoAlbum::handleKey_7()
	{}

	void PhotoAlbum::handleKey_8()
	{}

	void PhotoAlbum::handleKey_9()
	{}


protected:

	/**
	 * setCurrentPic()  picture changes the pictures on the main display
	 */
	void setCurrentPic(int index)
	{}

	void loadPics()
	{
		float squareDiameter = .3;
        float z = 0;
        float offset = .025;
			
        int ii=0;
		for(int i = -1; i<2; i++) {
	   		for (int j =- 1; j<2; j++) {
                cout << "Adding square " << ii << " at: " << i * squareDiameter + offset*i<< ", " << j * squareDiameter + offset*j<< ", " << z << endl;
                //_interpolation.push_back(new TimedInterpolation(2000, this));
			   	pics.push_back(new RectangularPrism(
                                    new Point3D(i*squareDiameter + offset*i, j*squareDiameter + offset*j, z),
                                    squareDiameter, squareDiameter, squareDiameter,
                                    new Paint(Color::BLUE, Color::WHITE, Paint::HEIGHT_BASED)
                                ));
                ++ii;
			}
		}
	}

private:

    vector<RectangularPrism*> pics; RectangularPrism *a,*b,*c;
    String2D * s;
    //vector<TimedInterpolation*> _interpolation;

};	

	
/**
 *  Tester Main
 */
int main(int argc, char **argv)
{
	PhotoAlbum * demo = new PhotoAlbum(); 
    return 0;
}

