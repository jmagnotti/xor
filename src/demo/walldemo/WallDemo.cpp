#include "../../xor.h"
#include "../../../include/SDL_syswm.h"


using namespace XOR;

	static const float DX_OB = 0.0001f;
	static const float DX_OM = 0.01f;
	static const float DX_FB = 0.01f;
	static const float DX_FM = 1.0f;


class WallDemo : public DefaultKeyboardListener, DefaultMouseListener
{

public:

	Object3D *tModels[3];


   /* 
  	* Constructor
 	*/
	WallDemo(int i, int j, int w, int h, int xpos, int ypos)
	{
		char buffer[100];
		sprintf(buffer, "i = %d  j = %d", i, j);

        Controller * ctrl = Controller::GetInstance(InputEventProxyFactory::GetInstance());
        ctrl->defaultConfiguration();

        ctrl->getKeyboard()->addListener(this);
		ctrl->getMouse()->addListener(this);

        ctrl->setModel(new String2D(buffer));

		ctrl->getViewer()->setWallOffset(i,j);
		ctrl->getViewer()->setWindowDimension(new Dimension2D((float)w, (float)h));

		wallMode = Viewer::WALL_MODE_STANDARD;
		ctrl->getViewer()->setWallMode(wallMode);

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

		ctrl->getViewer()->incrementTranslation(new Vector3D(50,50,50));
		ctrl->getViewer()->setFocalPoint(new Vector3D(0,0,0));
		//ctrl->getViewer()->setFocalPoint(new Vector3D(-80,-35,0));

        //ctrl->getModel()->addObject("white", 
				//new Cube(new Vector3D(.5,.5,.5), 1, new Paint(Color::WHITE)));
        //ctrl->getModel()->addObject("blue", 
				//new Cube(new Vector3D(0,0,5), 1, new Paint(Color::BLUE)));
        //ctrl->getModel()->addObject("green", 
				//new Cube(new Vector3D(0,5,0), 1, new Paint(Color::GREEN)));
        //ctrl->getModel()->addObject("red", 
				//new Cube(new Vector3D(5,0,0), 1, new Paint(Color::RED)));

		TextureFactory * factory = TextureFactory::GetInstance();

		ctrl->getModel()->addObject("white", 
				new CompiledObject3D(new Cube(
						new Vector3D(.5,.5,.5), 1, 
						new Paint(Color::WHITE, Paint::HEIGHT_BASED, 
							factory->createTexture("../coordinatesystem/images/white.png")))));
		ctrl->getModel()->addObject("blue",	 
				new CompiledObject3D(new Cube(
						new Vector3D(0,0,5), 1, 
						new Paint(Color::WHITE, Paint::HEIGHT_BASED, 
							factory->createTexture("../coordinatesystem/images/z_blue.png")))));
		ctrl->getModel()->addObject("green", 
				new CompiledObject3D(new Cube(
						new Vector3D(0,5,0), 1, 
						new Paint(Color::WHITE, Paint::HEIGHT_BASED, 
							factory->createTexture("../coordinatesystem/images/y_green.png")))));
		ctrl->getModel()->addObject("red", 	 
				new CompiledObject3D(new Cube(
						new Vector3D(5,0,0), 1, 
						new Paint(Color::WHITE, Paint::HEIGHT_BASED, 
							factory->createTexture("../coordinatesystem/images/x_red.png")))));

		tModels[0] = new CompiledObject3D(ModelFactory::GetInstance()->createModel(
				"../modeldemo/models/ant01.ms3d"));
		tModels[1] = new CompiledObject3D(ModelFactory::GetInstance()->createModel(
				"../modeldemo/models/turtle1.ms3d"));
		tModels[1]->incrementTranslation(new Vector3D(0,0,50));
		tModels[2] = new CompiledObject3D(ModelFactory::GetInstance()->createModel(
				"../modeldemo/models/f360.ms3d"));
		tModels[2]->incrementTranslation(new Vector3D(-100,0,50));
		tModels[2]->incrementRotation(Orientation::THETA, 90.0f, NULL);

		ctrl->getModel()->addObject("model1", tModels[0]);
		ctrl->getModel()->addObject("model2", tModels[1]);
		ctrl->getModel()->addObject("model3", tModels[2]);

        ctrl->run();
	}

	//void handleKey_l()
	//{
		//cout << "LOOK AT ORIGIN" << endl;
		//Controller::GetInstance(NULL)->getViewer()->setFocalPoint(new Vector3D(0,0,0));
	//}

	void handleKey_p()
	{ Controller::GetInstance(NULL)->getViewer()->print(); }

	void handleKey_a()
	{ Controller::GetInstance(NULL)->getViewer()->incrementRotation(0, 10.0f, new TimedInterpolation(300,NULL)); }
	void handleKey_d()
	{ Controller::GetInstance(NULL)->getViewer()->incrementRotation(0, -10.0f, new TimedInterpolation(300,NULL)); }
	void handleKey_w()
	{ Controller::GetInstance(NULL)->getViewer()->walk(1.0f, new TimedInterpolation(300,NULL)); }
	void handleKey_s()
	{ Controller::GetInstance(NULL)->getViewer()->walk(-1.0f, new TimedInterpolation(300,NULL)); }
	void handleKey_q()
	{ Controller::GetInstance(NULL)->getViewer()->incrementRotation(2, 5.0f, new TimedInterpolation(300,NULL)); }
	void handleKey_e()
	{ Controller::GetInstance(NULL)->getViewer()->incrementRotation(2, -5.0f, new TimedInterpolation(300,NULL)); }
	void handleKey_c()
	{ Controller::GetInstance(NULL)->getViewer()->incrementRotation(1, 5.0f, new TimedInterpolation(300,NULL)); }
	void handleKey_z()
	{ Controller::GetInstance(NULL)->getViewer()->incrementRotation(1, -5.0f, new TimedInterpolation(300,NULL)); }

    void handleKey_C()
    { Controller::GetInstance(NULL)->getViewer()->clear(); }

	void handleKey_Left()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallOffset(-1,0); }
	void handleKey_Right()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallOffset(1,0); }
	void handleKey_Up()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallOffset(0,1); }
	void handleKey_Down()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallOffset(0,-1); }
    void handleKey_RBracket()
    { Controller::GetInstance(NULL)->getViewer()->incrementTranslation(new Vector3D(0,0,1)); }
    void handleKey_LBracket()
    { Controller::GetInstance(NULL)->getViewer()->incrementTranslation(new Vector3D(0,0,-1)); }

	void handleKey_y()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewOffsetBase(0.0f-(DX_OB)); }
	void handleKey_Y()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewOffsetBase(0.0f-(DX_OB)*10); }
	void handleKey_u()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewOffsetBase(DX_OB); }
	void handleKey_U()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewOffsetBase(DX_OB*10); }

	void handleKey_h()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewOffsetModifier(0.0f-(DX_OM)); }
	void handleKey_H()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewOffsetModifier(0.0f-(DX_OM)*10); }
	void handleKey_j()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewOffsetModifier(DX_OM); }
	void handleKey_J()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewOffsetModifier(DX_OM*10); }

	void handleKey_n()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewFovBase(0.0f-(DX_FB)); }
	void handleKey_N()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewFovBase(0.0f-(DX_FB)*10); }
	void handleKey_m()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewFovBase(DX_FB); }
	void handleKey_M()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewFovBase(DX_FB*10); }

	void handleKey_i()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewFovModifier(0.0f-(DX_FM)); }
	void handleKey_I()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewFovModifier(0.0f-(DX_FM)*10); }
	void handleKey_o()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewFovModifier(DX_FM); }
	void handleKey_O()
	{ Controller::GetInstance(NULL)->getViewer()->incrementWallViewFovModifier(DX_FM*10); }
	
	void handleKey_l()
	{
		if (wallMode == Viewer::WALL_MODE_STANDARD)
			wallMode = Viewer::WALL_MODE_IMMERSIVE;
		else
			wallMode = Viewer::WALL_MODE_STANDARD;
		Controller::GetInstance(NULL)->getViewer()->setWallMode(wallMode);
	}

	void handleMouseMotion(MouseMotionEvent * mme)
	{
		Mouse * mouse = Controller::GetInstance(NULL)->getMouse();

		if (mouse->isLeftButtonDown()) {
			// rotate camera
			float xChange = (float)(mouse->getCurrentX() - mouse->getPreviousX()) / 2.0f;
			float yChange = (float)(mouse->getCurrentY() - mouse->getPreviousY()) / 2.0f;

			Controller::GetInstance(NULL)->getViewer()->incrementRotation(
					Orientation::THETA, -xChange, new TimedInterpolation(100,NULL));
			Controller::GetInstance(NULL)->getViewer()->incrementRotation(
					Orientation::PHI, -yChange, new TimedInterpolation(100,NULL));
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

	static const float ROTATE_CHANGE = 5.0f;
	static const float TRANSLATE_CHANGE = 0.2f;

	int wallMode;

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

