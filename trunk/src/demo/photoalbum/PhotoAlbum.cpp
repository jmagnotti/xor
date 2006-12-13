#include "../../xor.h"


using namespace std;

using namespace XOR;


class PhotoAlbum : public DefaultKeyboardListener, public Renderable
{

public:

   /* 
  	* Constructor
 	*/
	PhotoAlbum()
	{

        Controller * ctrl = Controller::GetInstance();
		ctrl->defaultConfiguration();

		ctrl->getKeyboard()->addListener(this);
       
        a = new Cube(new Point3D(0,-1,-1), .5f, new Paint(Color::RED, Paint::HEIGHT_BASED));
        b = new Cube(new Point3D(-1,0,-1), .5f, new Paint(Color::GREEN, Paint::HEIGHT_BASED));
        c = new Cube(new Point3D(-1,-1,-1), .5f, new Paint(Color::BROWN, Paint::HEIGHT_BASED));

		loadPics();

        s = new String2D("PHOTO DEMO"); // this is a kludge, FIXME 
        ctrl->setModel(this);

        ctrl->run();
	}

    
    void render()
    {
        s->render();

        vector<Square3D*>::iterator iter = pics.begin();
        vector<Square3D*>::iterator end = pics.end();

        while (iter != end) { 
            (*iter)->render();
            iter++;
        }
    }
 

	/**
	 * When you hit the 0 key, all the pictures are set back to 
	 * the grid configuration
	 */
	void PhotoAlbum::handleKey_0()
	{
		cout << Controller::GetInstance()->getViewer()->getOrientation()->getFocalPoint()->toString() << endl;
	}

//-- For all other key presses, the corresponding image (QUAD) is
// made to go quasi-full screen
	
	void PhotoAlbum::handleKey_1()
	{ 
         
    }

	void PhotoAlbum::handleKey_2()
	{}
	
	void PhotoAlbum::handleKey_3()
	{}
	
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
	{
		
	}

	void loadPics()
	{
		float squareDiameter = .3;
        float z = 0;
        float offset = .05;
			
		for(int i=-1; i<2; i++) {
	   		for (int j=-1; j<2; j++) {
                cout << "Adding square at: " << i *squareDiameter << ", " << j * squareDiameter << ", " << z << endl;

			   	pics.push_back(new Square3D(
                                    new Point3D(i * squareDiameter + offset*i, j * squareDiameter + offset*j, z),
                                    squareDiameter,
                                    new Paint( (i+1)*.3, (j+1)*.3, (j+i+1)*.3)
                                ));
			}
		}
	}
	

private:

    vector<Square3D*> pics;
    Cube *a,*b,*c;
    String2D *s;

};	

	
/**
 *  Tester Main
 */
int main(int argc, char **argv)
{
	PhotoAlbum * demo = new PhotoAlbum(); 

    return 0;
}

