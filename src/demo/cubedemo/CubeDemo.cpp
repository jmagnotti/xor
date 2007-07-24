#include "../../xor.h"

using namespace XOR;

class CubeDemoConfig : public XavierConfiguration
{
public:

	CubeDemoConfig()
	{
	}

	EventFactory * getEventFactory() const
	{
		return FullEventProxyFactory::GetInstance();
	}

	Dimension2D * getWindowSize() const
	{
		return new Dimension2D(900.0, 600);
	}

	Uint32 getVideoFlags()
	{
		return XavierConfiguration::getVideoFlags();
	}

};

class TestShape : public Object3D
{

public:
	TestShape()//float x, float y, float width)
	{
	}

	Dimension3D * getDimension()
	{
	}

	Vector3D * getBaseVector()
	{
	}

	void renderObject()
	{
		drawTri(0, 0, 5, 30);
	}

	void drawTri(float x, float y, float size, int limit)
	{
		if (limit == 0)
		{
			glBegin(GL_TRIANGLES);
			glVertex3f(x + size/2.0, y, 0);
			glVertex3f(x, y + (size/2.0)*1.73, 0);
			glVertex3f(x - size/2.0, y, 0);

			glVertex3f(x + size/2.0, y, -1);
			glVertex3f(x, y + (size/2.0)*1.73, -1);
			glVertex3f(x - size/2.0, y, -1);
			glEnd();

			glBegin(GL_LINES);
			glVertex3f(x + size/2.0, y, 0);
			glVertex3f(x + size/2.0, y, -1);

			glVertex3f(x, y + (size/2.0)*1.73, -1);
			glVertex3f(x, y + (size/2.0)*1.73, 0);

			glVertex3f(x - size/2.0, y, -1);
			glVertex3f(x - size/2.0, y, 0);

			glEnd();
		}
		else if (limit > 0&& limit < 10)
		{
			glColor3f(limit*.3, .6, .6*limit);
			drawTri(x, y + (size/4.0)*1.73, size/2.0, limit -1);
			drawTri(x + size/4.0, y, size/2.0, limit -1);
			drawTri(x - size/4.0, y, size/2.0, limit -1);
		}
		else
		{
			drawTri(x, y, size, 9);
		}
	}

private:
	float x;
	float y;
	float width;

};

/**
 * Demonstrates creation of an InputEventProxyFactory to multicast Keyboard and
 * Mouse events over the wire. Also uses a Paint with a gradient.
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class CubeDemo
{

public:

	CubeDemo()
	{
		Controller * ctrl;
		// the InputEventProxyFactory will send out Keyboard and Mouse events
		// over multicast
		ctrl = Controller::GetInstance(new CubeDemoConfig());

		ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
		ctrl->getMouse()->addListener(new DefaultMouseListener());
		ctrl->setModel(new String2D("testing"));

		//Object3DCollection * collection = new Object3DCollection();

		// -- begin array 
		/*TestShape * ts[4];
		 for(int ii = 0; ii < 4; ii+)
		 {
		 §
		 }
		 */
		TestShape * t0 = new TestShape();
		//t0->incrementTranslation(new Vector3D(0,-3,0));

		//TestShape * t1 = new TestShape();
		//t1->incrementRotation(Orientation::ROLL, 90);
		//t1->incrementTranslation(new Vector3D(3,0,0));

		//TestShape * t2 = new TestShape();
		//t2->incrementRotation(Orientation::ROLL, 180);
		//t2->incrementTranslation(new Vector3D(0,3,0));

		//TestShape * t3 = new TestShape();
		//t3->incrementRotation(Orientation::ROLL, 270);
		//t3->incrementTranslation(new Vector3D(-3,0,0));

		//collection->addObject3D(t0);
		//collection->addObject3D(t1);
		//collection->addObject3D(t2);
		//collection->addObject3D(t3);

		// -- end loop*/

		Transformable3D * t = new Transformable3D(t0);
		ctrl->getModel()->addObject("objs", new CompiledObject3D(t0));

		ctrl->getCamera()->getOrientation()->setPosition(new Vector3D(0,0,5));
		ctrl->getCamera()->getOrientation()->setFocalPoint(new Vector3D(0,0,0));

		// timer tests
		/*
		 PrintAllTicks *			pat = new PrintAllTicks();
		 PrintOccasionalTicks *	pot = new PrintOccasionalTicks();
		 PrintUniqueTick *		put = new PrintUniqueTick();
		 */
	}

	/**
	 * Tells the Controller to take charge. All interaction is now delegated to
	 * event handlers.
	 */
	void play(void)
	{
		Controller::GetInstance()->run();
	}

};

/**
 * Entry point of the application. All input parameters are ignored.
 * Although we are ignoring the parameters, the Macintosh linker fails if they
 * are not included in the method signature. This has more to do with the SDL
 * implementation than anything else.
 */
int main(int argc, char *argv[])
{
	CubeDemo * demo = new CubeDemo();

	Timer::SetInterval(30);
	demo->play();

	// required by the ANSI standard
	return 0;
}

