#include <math.h>
#include <sstream>

#include "../../xor.h"
#include "PrintMousePosition.h"
#include "CDGrid.h"
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


	Uint32 getVideoFlags()
	{
		return SDL_OPENGL;
//|SDL_FULLSCREEN;
	}

	const float * getBackgroundColor() { return Color::BLACK; }

};


vector<Vector2D*> buildPositionArray()
{

	vector<Vector2D*> _positions;
	int centerX, centerY, size;
	size = 210;
	centerY = 512;
	centerX = 640;

	int xoff = centerX - 55;
	int yoff = centerY - 55;

	int i=0;
	int radius = 150;
	double to_d = M_PI / 180.0;

	//the first element in the list is the fixation cross
	_positions.push_back(new Vector2D(xoff, yoff));

	for(int r=1; r<=3; r++) {
		for(double p=0 * (r-1)*22.5; p<360; p+= 90/r) {
			int rad  = radius*r;
			_positions.push_back( new Vector2D(xoff + rad*cos(to_d*p), yoff + rad*sin(to_d*p)) );
		}	
	}
	
	for(int i=0; i<_positions.size();i++)
		cout << _positions[i]->toString() << endl;

	return _positions;
}

int main(int argc, char * argv[])
{ 
	Controller * ctrl = Controller::GetInstance(new CDConfig());
    
    PrintAction * pa;    

    Dimension2D * iconSize;
    iconSize = new Dimension2D(95,95);

	CDGrid * cdg = new CDGrid();
	ActionItem * ai;
	Icon2D * icon;

	vector<Vector2D*> _positions = buildPositionArray();

	//we want a bunch of them
	for(int i=0; i<_positions.size();i++) {
		stringstream ss ("resources/image", ios::app | stringstream::in | stringstream::out);		
		ss << i; ss << ".jpg";
		pa = new PrintAction(i);
		icon = new Icon2D(_positions[i], iconSize, (char*)(ss.str().c_str()) );
		ai = new ActionItem(icon, pa);
		cdg->addAction(ai);
	}

    ctrl->setModel(cdg);
    ctrl->getMouse()->addListener(cdg);
    ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
    ctrl->run();

    return 0;
}
