#include "../../xor.h"


using namespace XOR;


class SineFunctionHF : public FunctionHeightFieldStrategy
{
	public:

		SineFunctionHF(double xmin, double xmax,
						double ymin, double ymax,
						double xres, double yres)
			: FunctionHeightFieldStrategy(xmin, xmax, ymin, ymax, xres, yres)
		{ }


		double f(double x, double y)
		{
/*			double a = 1.1;
			double b = a;
			double c = cos((x/a)*(x/a) + (y/b)*(y/b));
			return c;
            */
			return sin(x*2) * cos(y*2);
            
            //return sin(fabs(x) + fabs(y));
            //return x + 2*y;
		}
};


class TerrainConfig : public XavierConfiguration
{
    public :
        TerrainConfig()
        {}

        bool isGLFogEnabled()
        {
            false;
        }

        EventFactory * getEventFactory()
        {
            return InputEventHandlerFactory::GetInstance();
        }
};

class TerrainDemo : public DefaultKeyboardListener, DefaultMouseListener
{

public:

	Controller * ctrl; 

   /* 
  	* Constructor
 	*/
	TerrainDemo()
	{
        ctrl = Controller::GetInstance(new TerrainConfig());

        ctrl->getKeyboard()->addListener(this);
		ctrl->getMouse()->addListener(this);

        ctrl->setModel(new String2D("Heightfield Test"));

		ctrl->getCamera()->getOrientation()->setPosition(new Vector3D(10,10,10));
		ctrl->getCamera()->getOrientation()->setFocalPoint(new Vector3D(0,0,0));

		TextureFactory * factory = TextureFactory::GetInstance();
		
		ctrl->getModel()->addObject("white", 
		       new CompiledObject3D(new Cube(
		               new Vector3D(0,0,0), 1, 
		               new Paint(Color::WHITE))));
		ctrl->getModel()->addObject("blue",	 
			   new CompiledObject3D(new Cube(
					   new Vector3D(0,0,5), 1, 
					   new Paint(Color::BLUE))));
		ctrl->getModel()->addObject("green", 
			   new CompiledObject3D(new Cube(
					   new Vector3D(0,5,0), 1, 
					   new Paint(Color::GREEN))));
		ctrl->getModel()->addObject("red", 	 
			   new CompiledObject3D(new Cube(
					   new Vector3D(5,0,0), 1, 
					   new Paint(Color::RED))));
						//new Paint(Color::WHITE, Paint::HEIGHT_BASED,
						//TextureFactory::GetInstance()->createTexture("images/edhu08M.png")))));

		double m[5][5];
		m[0][0] = 4.0; m[0][1] = 0.0; m[0][2] = 4.0; m[0][3] = 0.0; m[0][4] = 0.0;
		m[1][0] = 0.0; m[1][1] = 0.0; m[1][2] = 4.0; m[1][3] = 0.0; m[1][4] = 0.0;
		m[2][0] = 2.0; m[2][1] = 2.0; m[2][2] = 4.0; m[2][3] = 2.0; m[2][4] = 2.0;
		m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 4.0; m[3][3] = 0.0; m[3][4] = 0.0;
		m[4][0] = 0.0; m[4][1] = 0.0; m[4][2] = 4.0; m[4][3] = 0.0; m[4][4] = 0.0;

		HeightField * hf = HeightFieldFactory::GetInstance()->
			//buildHeightField(new NullHeightFieldStrategy());
			//buildHeightField(new FunctionHeightFieldStrategy(-3.0, 3.0, -3.0, 3.0, 0.5, 0.5));
			//buildHeightField(new SineFunctionHF(-3.0, 3.0, -3.0, 3.0, 0.5, 0.5));
			buildHeightField(new ImageHeightFieldStrategy("images/hf2.png"));
			//buildHeightField(new MatrixHeightFieldStrategy((double**)m,5,5));
		hf->setHeightScale(5.0f);

		hf->setPaint(new Paint(Color::WHITE, Paint::HEIGHT_BASED,
					//TextureFactory::GetInstance()->createTexture("images/plnt10M.jpg")));
					//TextureFactory::GetInstance()->createTexture("images/ahul01M.jpg")));
					TextureFactory::GetInstance()->createTexture("images/big_texture.jpg")));
					//TextureFactory::GetInstance()->createTexture("images/ahul08M.jpg")));
					//TextureFactory::GetInstance()->createTexture("images/grass.png")));

		ctrl->getModel()->addObject("field", new CompiledObject3D(hf));

        ctrl->run();
	}

	//void handleKey_l()
	//{
		//cout << "LOOK AT ORIGIN" << endl;
		//ctrl->getCamera()->setFocalPoint(new Vector3D(0,0,0));
	//}


	//void handleKey_c()
	//{
		//ctrl->getCamera()->incrementRotation(1, 5.0f, new TimedInterpolation(300,NULL));
	//}

	//void handleKey_z()
	//{
		//ctrl->getCamera()->incrementRotation(1, -5.0f, new TimedInterpolation(300,NULL));
	//}

    //void handleKey_C()
    //{
        //ctrl->getCamera()->clear();
    //}

    //void handleKey_RBracket()
    //{
        //ctrl->getCamera()->incrementTranslation(new Vector3D(0,0,1));
    //}

    //void handleKey_LBracket()
    //{
        //ctrl->getCamera()->incrementTranslation(new Vector3D(0,0,-1));
    //}

	//void handleKey_k()
	//{
		//cout << "handling..." << endl; 
		//int speed = 2000;
		//int wait  = 2000;

		//Orientation * o1 = ctrl->getCamera()->cloneOrientation();
		//o1->incrementTranslation(new Vector3D(15.0f,0.0f,0.0f), NULL);
		//Orientation * o2 = ctrl->getCamera()->cloneOrientation();
		//o2->incrementTranslation(new Vector3D(15.0f,15.0f,0.0f), NULL);
		//Orientation * o3 = ctrl->getCamera()->cloneOrientation();
		//o3->incrementTranslation(new Vector3D(15.0f,15.0f,15.0f), NULL);
		//o3->incrementRotation(Orientation::ROLL, 40.0f);

		//Waypoint * wp3 = new Waypoint(o3, speed, wait, NULL);
		//Waypoint * wp2 = new Waypoint(o2, speed, wait, wp3);
		//Waypoint * wp1 = new Waypoint(o1, speed, wait, wp2);

		//wp1->apply(ctrl->getCamera());
	//}
	
private:

	static const float ROTATE_CHANGE = 5.0f;
	static const float TRANSLATE_CHANGE = 0.2f;
};


/**
 *  Tester Main
 */
int main(int argc, char **argv)
{
	TerrainDemo * demo = new TerrainDemo(); 
    return 0;
}

