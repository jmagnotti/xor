#include "Experiment.h"
#include "AutoPilotState.h"

#include "../../../xor.h"

using namespace XOR;

class Record : public XavierConfiguration
{
public:

	unsigned int getTimerInterval() {
		return 10;
	}

	Record() {}
	~Record() {}

	const float * getBackgroundColor() {
		return Color::BLACK;
	}

	EventFactory * getEventFactory() const {
		return new EventRecorderFactory(InputEventProxyFactory::GetInstance());
	}

	bool isGLFogEnabled() {
		return true;
	}

	int getGLFogStart() {
		return 300;
	}

	int getGLFogEnd() {
		return 400;
	}

	double getFarClip() {
		return 2000.0;
	}

	double getNearClip() {
		return .01;
	}

	Dimension2D * getWindowSize() const {
		return new Dimension2D(1680, 1050);
	}
};

int main()
{
	Controller * ctrl = Controller::GetInstance(new Record);

	Experiment * e = new Experiment(ctrl);

	ctrl->getKeyboard()->addListener(e);
	ctrl->getMouse()->addListener(e);

//	e->setState(PracticeState::GetInstance(e));
	e->setState(AutoPilotState::GetInstance(e));

	ctrl->run();
}
