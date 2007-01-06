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
	//ctrl->getViewer()->incrementTranslation(new Dimension3D(0,0,-1));

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
	void handleKey_0()
	{
		//cout << Controller::GetInstance()->getViewer()->getFocalPoint()->toString() << endl;
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
		float offset = .1;
				
		int ii=0;
		for(double i = -3; i<3; i++) {
	   		for (double j =- 3; j<3; j++) {
                cout << "Adding square " << ii << " at: " << i * squareDiameter + offset*i<< ", " << j * squareDiameter + offset*j<< ", " << z << endl;
			   	pics.push_back(new RectangularPrism(
					new Point3D(i*squareDiameter + offset*i, j*squareDiameter + offset*j, z),
					squareDiameter, squareDiameter, squareDiameter,
					new Paint(.1,.1f*(i+2), .1f*(i+3), Paint::HEIGHT_BASED)
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

