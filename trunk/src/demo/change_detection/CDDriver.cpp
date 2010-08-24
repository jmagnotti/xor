#include <math.h>
//#include <sstream>

#include "../../xor.h"
#include "PrintMousePosition.h"
#include "CDGrid.h"
#include "CDStartState.h"
#include "PrintAction.h"
#include "ActionItem.h"
#include "Icon2D.h"

using namespace XOR;
using namespace std;

class CDConfig : public XavierConfiguration 
{
public:

	CDConfig(){}

	Dimension2D * getWindowSize() const { return new Dimension2D(1280,1024); }	

	Uint32 getVideoFlags() { return (SDL_OPENGL|SDL_FULLSCREEN); }

	const float * getBackgroundColor() { return Color::BLACK; }

	unsigned int getTimerInterval() { return 15; }

};


vector<Vector2D*> buildPositionArray()
{
	vector<Vector2D*> _positions;
	int centerX, centerY;
	centerX = WIDTH/2;
	centerY = HEIGHT/2;

	int xoff = centerX - 128/2;
	int yoff = centerY - 128/2;

	int radius = 120;
	double to_d = M_PI / 180.0;

	//the first element in the list is the fixation cross
	_positions.push_back(new Vector2D(xoff, yoff));

	for(int r=1; r<=3; r++) {
		for(double p=0; p<360; p+= 90/r) {
			int rad  = radius*r;
			_positions.push_back( new Vector2D(xoff + rad*cos(to_d*p), yoff + rad*sin(to_d*p)) );
		}	
	}
	for(int i=0; i<_positions.size(); i++) cout << i << " " << _positions[i]->toString() << endl;
	return _positions;
}

int main(int argc, char * argv[])
{ 
	Controller * ctrl = Controller::GetInstance(new CDConfig());

	//hide the mouse
	SDL_ShowCursor(0);
	SDL_WM_GrabInput(SDL_GRAB_ON);
	
	//Print action notifies the appropriate CDState of the clicked action item
    PrintAction * pa;    
    Dimension2D * iconSize = new Dimension2D(32,32);

	CDGrid * cdg = new CDGrid();
	ActionItem * ai;
	Paint * p;
	Rectangle2D * rect;

	TextureFactory * tf = TextureFactory::GetInstance();
	vector<Vector2D*> _positions = buildPositionArray();

	//cout << _positions.size() << endl;

	pa = new PrintAction(0);
	Vector2D *offset = new Vector2D(50,50);
	p = new Paint(Color::YELLOW);
	rect = new Rectangle2D((*_positions[0])+offset, new Dimension2D(32,32), p);

	delete offset;

	ai = new ActionItem(pa, rect);
	cdg->addAction(ai);

	//for each position, build a picture and assign an action 
	//start at i=1 to skip fixation point
	for(int i=1; i<_positions.size(); i++) {
		pa = new PrintAction(i);
		p = new Paint(Color::WHITE);//tf->createTexture("C:/images/red.jpg"));//ss.str().c_str()));
		rect = new Rectangle2D(_positions[i], iconSize, p);
		ai = new ActionItem(pa, rect);
		cdg->addAction(ai);
	}

    ctrl->setModel(cdg);

    ctrl->getMouse()->addListener(cdg);
    ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());

	Session::GetInstance("changeNoChange.xml");
	CDStartState * cdss = CDStartState::GetInstance(cdg);
	cdss->activate();

    ctrl->run();

    return 0;
}
