#include <math.h>

#include "../../xor.h"
#include "PrintMousePosition.h"
#include "CDGrid.h"
#include "CDStartState.h"
#include "PrintAction.h"
#include "ActionItem.h"
#include "Icon2D.h"

#include "SerialPortTimer.h"

using namespace XOR;
using namespace std;

#define WIDTH 1280
#define HEIGHT 1024

#define STIMULUS_WIDTH  64
#define STIMULUS_HEIGHT 64

//STROOP
//#define STIMULUS_WIDTH 128 
//#define STIMULUS_HEIGHT 96 

// STROOP
//#define OFFSET .20 * STIMULUS_WIDTH 

#define OFFSET .50 * STIMULUS_WIDTH 

#define LINE_UP_LEFT_OFFSET 160

class CDConfig: public XavierConfiguration {
public:
	CDConfig() { }

	Dimension2D * getWindowSize() const { return new Dimension2D(WIDTH, HEIGHT); }

	Uint32 getVideoFlags() { return (SDL_OPENGL | SDL_FULLSCREEN); }

	const float * getBackgroundColor() { return Color::BLACK; }

	unsigned int getTimerInterval() { return 15; }
};


class AutoTimer : public TimerListener {
public:

    AutoTimer () 
    { }

    void handleTick()
    {
        cout << "Tick" << endl;
        SerialPortTimer::GetInstance()->notifyListeners();
    }

    void start()
    {
        IntervalTimer::GetInstance()->addListener(this, 1500, true);
    }

};


vector<Vector2D*> buildPositionArray() {
	vector<Vector2D*> _positions;
	int centerX, centerY;
	centerX = WIDTH / 2;
	centerY = HEIGHT / 2;

	int xoff = centerX - STIMULUS_WIDTH/ 2;
	int yoff = centerY - STIMULUS_HEIGHT/ 2;

	int radius = STIMULUS_WIDTH + OFFSET;
	double to_rad = M_PI / 180.0;

	//the first element in the list is the fixation cross
	_positions.push_back(new Vector2D(xoff, yoff));

	for (int r = 1; r <= 3; r++) {
		for (double p = 0; p < 360; p += 90 / r) {
			int rad = radius * r;
			_positions.push_back(new Vector2D(xoff + rad * cos(to_rad * p), yoff + rad * sin(to_rad * p)));
		}
	}
    //now we need to build the positions for the "line-up" view
    for(int i=0; i<8; i++) {
        _positions.push_back(new Vector2D(LINE_UP_LEFT_OFFSET + i* (STIMULUS_WIDTH*2), yoff));
    }    

    Vector2D * halfSize = new Vector2D(STIMULUS_WIDTH/2, STIMULUS_HEIGHT/2);
    cout << "Stim Centers" << endl;
	for (int i = 0; i < _positions.size(); i++)
		cout << i << " " << ((*(_positions[i]))+halfSize)->toString() << endl;

	return _positions;
}

int main(int argc, char * argv[]) {
	Controller * ctrl = Controller::GetInstance(new CDConfig());

    //SDL_ShowCursor(NULL);
    SDL_ShowCursor(SDL_DISABLE);

	//Print action notifies the appropriate CDState of the clicked action item
	PrintAction * pa;
	Dimension2D * iconSize = new Dimension2D(STIMULUS_WIDTH, STIMULUS_HEIGHT);

	CDGrid * cdg = new CDGrid();
	ActionItem * ai;
	Paint * p;
	Rectangle2D * rect;

	TextureFactory * tf = TextureFactory::GetInstance();
	vector<Vector2D*> _positions = buildPositionArray();

	pa = new PrintAction(0);

	p = new Paint(Color::YELLOW);
	rect = new Rectangle2D(_positions[0], iconSize, p);

	ai = new ActionItem(pa, rect);
	cdg->addAction(ai);

	//for each position, build a picture and assign an action 
	//start at i=1 to skip fixation point
	for (int i = 1; i < _positions.size(); i++) {
		pa = new PrintAction(i);
		rect = new Rectangle2D(_positions[i], iconSize, p);
		ai = new ActionItem(pa, rect);
		cdg->addAction(ai);
	}

	ctrl->setModel(cdg);
	ctrl->getMouse()->addListener(cdg);
	ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());

    ctrl->getTimer()->addListener(SerialPortTimer::GetInstance());

	if (argc > 3)
		Session::GetInstance(argv[1], argv[2], atoi(argv[3]));
	else if (argc > 2)
		Session::GetInstance(argv[1], argv[2], time(NULL));
	else if (argc > 1)
		Session::GetInstance(argv[1], "result.tmp");
	else
		Session::GetInstance("cncShortTrials.xml", "result.tmp");
	
    //dirty dirty
    //glLineWidth(3.0f);

	CDStartState * cdss = CDStartState::GetInstance(cdg);
	cdss->activate();


    //This makes things go automatically
    //AutoTimer * at = new AutoTimer();
    //at->start();
    //

	ctrl->run();

	return 0;
}

