#include "../../xor.h"
#include "../../shape/Square3D.h"
//#include <string>


using namespace std;
using namespace XOR;


class PhotoAlbum : public DefaultKeyboardListener
{

public:

   /* 
  	* Constructor
 	*/
	PhotoAlbum()
	{
        Controller * ctrl = Controller::GetInstance();
		// a nice big world to keep our pictures in
		//world = World::GetInstance();
		
		ctrl->defaultConfiguration();
		
		ctrl->getKeyboard()->addListener(this);
		
		//ctrl->setModel(new Square3D(new Point3D(-200,-1000,0), 1.0f, new Paint(Color::RED, Paint::HEIGHT_BASED)));
			//	world);
		loadPics();
		displayPics();
        //ctrl->getViewer()->getOrientation()->incrementPosition(new Point3D(0,0,9));
        //ctrl->getViewer()->getOrientation()->setFocalPoint(new Point3D(0,0,0));
        ctrl->run();
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

private:

	Square3D * _pictures[9];
	//World * world;

protected:
	/**
	 * setCurrentPic()  picture changes the pictures on the main display
	 */
	void setCurrentPic(int index)
	{
		
	}

	void loadPics()
	{
		float squareDiameter = .1;
			
		for(int i=0; i<3; i++)
		{
	   		for (int j=0; j<3; j++)
			{
			   	_pictures[3*i + j] = new Square3D(
							new Point3D(i * squareDiameter, j * squareDiameter, 0),
							squareDiameter,
							new Paint(.2, .1 * i, .3 * j));
			}
		}
	}
	
	void displayPics()
	{
		World * world = Controller::GetInstance()->getModel();
		for(int i = 0; i < 9; i++) {
			string name = "Quad " + i;
			cout << "adding: " << name << " to world." << endl;
			world->addRenderable((char*)name.c_str(), (Renderable*)_pictures[i]);
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

