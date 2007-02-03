#include "../../xor.h"


using namespace XOR;


class ModelDemo : public DefaultKeyboardListener, DefaultMouseListener
{

public:

	Model *tModel;

   /* 
  	* Constructor
 	*/
	ModelDemo()
	{
        Controller * ctrl = Controller::GetInstance(LocalEventHandlerFactory::GetInstance());
        ctrl->defaultConfiguration();

		ctrl->removeDefaultKeyboardListener();
        ctrl->getKeyboard()->addListener(this);
		ctrl->removeDefaultMouseListener();
		ctrl->getMouse()->addListener(this);

        ctrl->setModel(new String2D("Model Test"));

		ctrl->getViewer()->incrementTranslation(new Dimension3D(10,10,10));
		ctrl->getViewer()->setFocalPoint(new Dimension3D(0,0,0));
		
		//tModel = ModelFactory::GetInstance()->createModel("data/f360.ms3d");
		tModel = ModelFactory::GetInstance()->createModel("data/ant01.ms3d");
		//tModel = ModelFactory::GetInstance()->createModel("data/ant02.ms3d");
		//tModel = ModelFactory::GetInstance()->createModel("data/dwarf1.ms3d");
		//tModel = ModelFactory::GetInstance()->createModel("data/dwarf2.ms3d");
		//tModel = ModelFactory::GetInstance()->createModel("data/turtle1.ms3d");
		ctrl->getModel()->addRenderable("model", tModel);

        ctrl->run();
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
		Controller::GetInstance()->getViewer()->walk(0.5f, new TimedInterpolation(300,NULL));
	}

	void handleKey_s()
	{
		Controller::GetInstance()->getViewer()->walk(-0.5f, new TimedInterpolation(300,NULL));
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

	void handleKey_g()
	{
		tModel->incrementRotation(Positionable::THETA,-360.0f, new TimedInterpolation(1000,NULL));
	}
	void handleKey_h()
	{
		tModel->incrementRotation(Positionable::PHI,-360.0f, new TimedInterpolation(1000,NULL));
	}
	void handleKey_j()
	{
		tModel->incrementRotation(Positionable::ROLL,-360.0f, new TimedInterpolation(1000,NULL));
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
	
private:

	static const float ROTATE_CHANGE = 5.0f;
	static const float TRANSLATE_CHANGE = 0.2f;
};


/**
 *  Tester Main
 */
int main(int argc, char **argv)
{
	ModelDemo * demo = new ModelDemo(); 
    return 0;
}

