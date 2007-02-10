#include "stdlib.h"

#include "../../xor.h"


using namespace XOR;


class ModelDemo : public DefaultKeyboardListener, DefaultMouseListener
{

public:

	Model *tModels[4];

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

		ctrl->getViewer()->incrementTranslation(new Dimension3D(50,50,50));
		ctrl->getViewer()->setFocalPoint(new Dimension3D(0,25,30));
		
		tModels[0] = ModelFactory::GetInstance()->createModel("models/ant01.ms3d");
		/*
		tModels[1] = ModelFactory::GetInstance()->createModel("models/dwarf1.ms3d");
		tModels[1]->incrementTranslation(new Dimension3D(-50,0,0));
		*/
		tModels[1] = ModelFactory::GetInstance()->createModel("models/turtle1.ms3d");
		tModels[1]->incrementTranslation(new Dimension3D(0,0,50));
		tModels[2] = ModelFactory::GetInstance()->createModel("models/f360.ms3d");
		tModels[2]->incrementTranslation(new Dimension3D(-100,0,50));
		tModels[2]->incrementRotation(Positionable::THETA, 90.0f);

		ctrl->getModel()->addObject("model1", new CompiledObject3D(tModels[0]));
		ctrl->getModel()->addObject("model2", new CompiledObject3D(tModels[1]));
		ctrl->getModel()->addObject("model3", new CompiledObject3D(tModels[2]));
		//ctrl->getModel()->addRenderable("model4", tModels[3]);

        ctrl->run();
	}

	void handleKey_a()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(
				0, 10.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_d()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(
				0, -10.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_w()
	{
		Controller::GetInstance()->getViewer()->walk
			(0.5f, new TimedInterpolation(300,NULL));
	}

	void handleKey_s()
	{
		Controller::GetInstance()->getViewer()->walk(
				-0.5f, new TimedInterpolation(300,NULL));
	}

	void handleKey_q()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(
				2, 5.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_e()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(
				2, -5.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_c()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(
				1, 5.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_z()
	{
		Controller::GetInstance()->getViewer()->incrementRotation(
				1, -5.0f, new TimedInterpolation(300,NULL));
	}

	void handleKey_g()
	{
		tModels[0]->incrementRotation(
				Positionable::THETA,-360.0f, new TimedInterpolation(1000,NULL));
	}
	void handleKey_h()
	{
		tModels[0]->incrementRotation(
				Positionable::PHI,-360.0f, new TimedInterpolation(1000,NULL));
	}
	void handleKey_j()
	{
		tModels[0]->incrementRotation(
				Positionable::ROLL,-360.0f, new TimedInterpolation(1000,NULL));
	}
	void handleKey_k()
	{
		int m = rand()%4;			// random model
		int a = rand()%3;			// random axis
		float r = 360.0f;			// fixed rotation
		int t = (rand()%3+2)*750;	// random time
		tModels[m]->incrementRotation(
				a, r, new TimedInterpolation(t,NULL));
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
	srand((unsigned)time(NULL));
	ModelDemo * demo = new ModelDemo(); 
    return 0;
}

