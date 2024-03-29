#include "../../xor.h"

#include <stdlib.h>
#include "SmoothMovementKeyHandler.h"

using namespace XOR;

class ViewerBox : public OrientationListener, public TimerListener
{

public: 

    ViewerBox(Vector3D * origin, Dimension3D * size, float buffer)
    {
        _bounds = new RectangularVolume(origin, size); 
		_buffer = buffer;
    }

    /**
     * relatively naive implementation
     */
    int handlePositionChange(Vector3D * position)
    {

        Containment * container = new Containment();

        // fill the containment object with information
        _bounds->contains(container, *position + _buffer);
        _bounds->contains(container, *position - _buffer);
		
		// we always to stop Y movement
        unsigned int mask = container->getInverseMask() | Containment::Y;
        return mask; 
    }

	inline void handleRotationChange(float angle, const Vector3D * axis)
    {}

	void handleTick()
	{
		cout << "TICK" << SDL_GetTicks() << endl;
	}

private:

    float _buffer;
    RectangularVolume * _bounds;
};

class Record : public XavierConfiguration
{
public:

	unsigned int getTimerInterval()
	{
		return 10;
	}

	Record()
	{}

	const float * getBackgroundColor() {
		return Color::BLACK;
	}
	EventFactory * getEventFactory() const {
		return new EventRecorderFactory(InputEventProxyFactory::GetInstance());
	}

	bool isGLFogEnabled()
	{
		return false;
	}

	double getFarClip()
	{
		return 2000.0;
	}

	double getNearClip()
	{
		return .00001;
	}

	bool isFullscreen()
	{
		return true;
	}

	Dimension2D * getWindowSize() const 
	{
		return new Dimension2D(1680, 1050);
	}
};

class PlayBack : public XavierConfiguration
{
public:

	PlayBack()
	{}

	EventFactory * getEventFactory() const {
		return new EventPlayerFactory(InputEventProxyFactory::GetInstance());
	}
};

class DistanceEstimationDemo
{
public:

	DistanceEstimationDemo(XavierConfiguration * conf)
	{
		Controller * ctrl = Controller::GetInstance(conf);

		TextureFactory * tf = TextureFactory::GetInstance();
		RectangularPrism * rp = new RectangularPrism(new Vector3D(-15,-4, 4),
				new Dimension3D(30, 20, -1000),
				new Paint(tf->createTexture("of_floor3.jpg")));

		ctrl->getCamera()->getOrientation()->addListener(
				new ViewerBox(rp->getBaseVector(), rp->getDimension(), 1.0f));

		Quadrilateral3D * temp = rp->removeFace(0); delete temp;

		// Add a keyboard listener that has a small set of key handlers
		ctrl->getKeyboard()->addListener(new SmoothMovementKeyHandler(1.0f));

		// Add basic mouse handling
		ctrl->getMouse()->addListener(new DefaultMouseListener());

		// sets the RectPrism as the main object in the world.
		ctrl->setModel(new CompiledObject3D(rp));
	}

	// this call runs the demo.
	void run()
	{
		Controller::GetInstance()->run();
	}

};

