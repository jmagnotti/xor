#include "../../xor.h"
#include "../../../include/SDL_syswm.h"


using namespace XOR;


class WallDemo : public DefaultKeyboardListener, DefaultMouseListener
{

public:

	Model *tModels[3];

   /* 
  	* Constructor
 	*/
	WallDemo(int i, int j, int w, int h, int xpos, int ypos)
	{
		char buffer[100];
		sprintf(buffer, "i = %d  j = %d", i, j);

        Controller * ctrl = Controller::GetInstance(LocalEventHandlerFactory::GetInstance());
        ctrl->defaultConfiguration();

		ctrl->removeDefaultKeyboardListener();
        ctrl->getKeyboard()->addListener(this);
		ctrl->removeDefaultMouseListener();
		ctrl->getMouse()->addListener(this);

        ctrl->setModel(new String2D(buffer));

		ctrl->getViewer()->setWallOffset(i,j);
		ctrl->getViewer()->setWindowDimension(new Dimension2D((float)w, (float)h));

		ctrl->getViewer()->setWallMode(Viewer::WALL_MODE_STANDARD);
		//ctrl->getViewer()->setWallMode(Viewer::WALL_MODE_IMMERSIVE);

		// move the window start position (linux/X11 dependent!)
		SDL_SysWMinfo info;
		SDL_VERSION(&info.version);
		int ret;
		ret = SDL_GetWMInfo(&info);
		if (ret > 0) {
#ifdef unix
			if (info.subsystem == SDL_SYSWM_X11) {
				info.info.x11.lock_func();
				XMoveWindow(info.info.x11.display, info.info.x11.wmwindow,
						 xpos, ypos);
				info.info.x11.unlock_func();
			}
#endif
		}

		ctrl->getViewer()->incrementTranslation(new Dimension3D(10,10,10));
		ctrl->getViewer()->setFocalPoint(new Dimension3D(0,0,0));
 
        ctrl->getModel()->addObject("white", 
				new Cube(new Vector3D(.5,.5,.5), 1, new Paint(Color::WHITE)));
        ctrl->getModel()->addObject("blue", 
				new Cube(new Vector3D(0,0,5), 1, new Paint(Color::BLUE)));
        ctrl->getModel()->addObject("green", 
				new Cube(new Vector3D(0,5,0), 1, new Paint(Color::GREEN)));
        ctrl->getModel()->addObject("red", 
				new Cube(new Vector3D(5,0,0), 1, new Paint(Color::RED)));

		tModels[0] = ModelFactory::GetInstance()->createModel(
				"../modeldemo/models/ant01.ms3d");
		tModels[1] = ModelFactory::GetInstance()->createModel(
				"../modeldemo/models/turtle1.ms3d");
		tModels[1]->incrementTranslation(new Dimension3D(0,0,50));
		tModels[2] = ModelFactory::GetInstance()->createModel(
				"../modeldemo/models/f360.ms3d");
		tModels[2]->incrementTranslation(new Dimension3D(-100,0,50));
		tModels[2]->incrementRotation(Positionable::THETA, 90.0f, NULL);

		ctrl->getModel()->addObject("model1", tModels[0]);
		ctrl->getModel()->addObject("model2", tModels[1]);
		ctrl->getModel()->addObject("model3", tModels[2]);

        ctrl->run();
	}

	void handleKey_l()
	{
		cout << "LOOK AT ORIGIN" << endl;
		Controller::GetInstance()->getViewer()->setFocalPoint(new Dimension3D(0,0,0));
	}

	void handleKey_p()
	{
		Controller::GetInstance()->getViewer()->printDebugInfo();
	}

	void handleKey_a()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(0, 10.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_d()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(0, -10.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_w()
	{
		Controller::GetInstance()->getViewer()->walk(5.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_s()
	{
		Controller::GetInstance()->getViewer()->walk(-5.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_q()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(2, 5.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_e()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(2, -5.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_c()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(1, 5.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_z()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(1, -5.0f, new TimedInterpolation(300,NULL));
	}

    void handleKey_C()
    {
        Controller::GetInstance()->getViewer()->clear();
    }

	void handleKey_Left()
	{
		Controller::GetInstance()->getViewer()->incrementWallOffset(-1,0);
	}

	void handleKey_Right()
	{
		Controller::GetInstance()->getViewer()->incrementWallOffset(1,0);
	}

	void handleKey_Up()
	{
		Controller::GetInstance()->getViewer()->incrementWallOffset(0,1);
	}

	void handleKey_Down()
	{
		Controller::GetInstance()->getViewer()->incrementWallOffset(0,-1);
	}

    void handleKey_RBracket()
    {
        Controller::GetInstance()->getViewer()->incrementTranslation(new Dimension3D(0,0,1));
    }

    void handleKey_LBracket()
    {
        Controller::GetInstance()->getViewer()->incrementTranslation(new Dimension3D(0,0,-1));
    }
	
	void handleMouseMotion(MouseMotionEvent * mme)
	{
		Mouse * mouse = Controller::GetInstance()->getMouse();

		if (mouse->isLeftButtonDown()) {
			// rotate camera
			float xChange = (float)(mouse->getCurrentX() - mouse->getPreviousX()) / 2.0f;
			float yChange = (float)(mouse->getCurrentY() - mouse->getPreviousY()) / 2.0f;

			Controller::GetInstance()->getViewer()->incrementRotation(
					Positionable::THETA, -xChange, new TimedInterpolation(100,NULL));
			Controller::GetInstance()->getViewer()->incrementRotation(
					Positionable::PHI, -yChange, new TimedInterpolation(100,NULL));
		}
	}
	
	void handleMouseButtonPressed(MouseButtonDown * mbd)
	{
		cout << "MOUSE DOWN: button=" << mbd->getButton() << endl;
	}

	void handleMouseButtonReleased(MouseButtonUp * mbu)
	{
		cout << "MOUSE UP: button=" << mbu->getButton() << endl;
	}
	
private:

	int _systype;

	static const float ROTATE_CHANGE = 5.0f;
	static const float TRANSLATE_CHANGE = 0.2f;
};


/**
 *  Tester Main
 */
int main(int argc, char **argv)
{
	if (argc == 3) {
		WallDemo * demo = new WallDemo(atoi(argv[1]), atoi(argv[2]), 800, 600, 0, 0); 
	} else if (argc == 7) {
		WallDemo * demo = new WallDemo(atoi(argv[1]), atoi(argv[2]), 
				atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6])); 
	} else {
		cout << "usage:    WallDemo <x-offset> <y-offset>" << endl;
		cout << "       or WallDemo <x-offset> <y-offset> <width> <height> <x-position> <y-position>" << endl;
	}
    return 0;
}

