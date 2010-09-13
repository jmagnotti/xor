#include <math.h>

#include "../../xor.h"
#include "PrintMousePosition.h"
#include "CDGrid.h"
#include "CDStartState.h"
#include "PrintAction.h"
#include "ActionItem.h"
#include "Icon2D.h"

using namespace XOR;
using namespace std;

#define WIDTH 1280
#define HEIGHT 1024

class CDConfig: public XavierConfiguration {
public:
	CDConfig() { }

	Dimension2D * getWindowSize() const { return new Dimension2D(WIDTH, HEIGHT); }

	Uint32 getVideoFlags() { return (SDL_OPENGL|SDL_FULLSCREEN); }

	const float * getBackgroundColor() { return Color::BLACK; }

	unsigned int getTimerInterval() { return 15; }
};

/* XPM */
static const char *arrow[] = {
  /* width height num_colors chars_per_pixel */
  "    32    32        3            1",
  /* colors */
  "X c #000000",
  ". c #ffffff",
  "  c None",
  /* pixels */
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "                                ",
  "0,0"
};

static SDL_Cursor * getCursor()
{
  int i, row, col;
  Uint8 data[4*32];
  Uint8 mask[4*32];
  int hot_x, hot_y;

  i = -1;
  for ( row=0; row<32; ++row ) {
    for ( col=0; col<32; ++col ) {
      if ( col % 8 ) {
        data[i] <<= 1;
        mask[i] <<= 1;
      } else {
        ++i;
        data[i] = mask[i] = 0;
      }
      switch (arrow[4+row][col]) {
        case 'X':
          data[i] |= 0x01;
          mask[i] |= 0x01;
          break;
        case '.':
          mask[i] |= 0x01;
          break;
        case ' ':
          break;
      }
    }
  }
  sscanf(arrow[4+row], "%d,%d", &hot_x, &hot_y);
  return SDL_CreateCursor(data, mask, 32, 32, hot_x, hot_y);
}
vector<Vector2D*> buildPositionArray() {
	vector<Vector2D*> _positions;
	int centerX, centerY;
	centerX = WIDTH / 2;
	centerY = HEIGHT / 2;

	int xoff = centerX - 64 / 2;
	int yoff = centerY - 64 / 2;

	int radius = 130;
	double to_d = M_PI / 180.0;

	//the first element in the list is the fixation cross
	_positions.push_back(new Vector2D(xoff, yoff));

	for (int r = 1; r <= 3; r++) {
		for (double p = 0; p < 360; p += 90 / r) {
			int rad = radius * r;
			_positions.push_back(new Vector2D(xoff + rad * cos(to_d * p), yoff + rad * sin(to_d * p)));
		}
	}
	for (int i = 0; i < _positions.size(); i++)
		cout << i << " " << _positions[i]->toString() << endl;
	return _positions;
}

int main(int argc, char * argv[]) {
	Controller * ctrl = Controller::GetInstance(new CDConfig());

	//hide the mouse
	//SDL_ShowCursor(0);
	SDL_SetCursor(getCursor());

	//Print action notifies the appropriate CDState of the clicked action item
	PrintAction * pa;
	Dimension2D * iconSize = new Dimension2D(64, 64);

	CDGrid * cdg = new CDGrid();
	ActionItem * ai;
	Paint * p;
	Rectangle2D * rect;

	TextureFactory * tf = TextureFactory::GetInstance();
	vector<Vector2D*> _positions = buildPositionArray();

	pa = new PrintAction(0);

	p = new Paint(Color::YELLOW);
	rect = new Rectangle2D(_positions[0], new Dimension2D(128, 128), p);

	ai = new ActionItem(pa, rect);
	cdg->addAction(ai);

	//for each position, build a picture and assign an action 
	//start at i=1 to skip fixation point
	for (int i = 1; i < _positions.size(); i++) {
		pa = new PrintAction(i);
		p = new Paint(Color::WHITE);
		rect = new Rectangle2D(_positions[i], iconSize, p);
		ai = new ActionItem(pa, rect);
		cdg->addAction(ai);
	}

	ctrl->setModel(cdg);
	ctrl->getMouse()->addListener(cdg);
	ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());

	if (argc > 3)
		Session::GetInstance(argv[1], argv[2], atoi(argv[3]));
	else if (argc > 2)
		Session::GetInstance(argv[1], argv[2], time(NULL));
	else if (argc > 1)
		Session::GetInstance(argv[1], "result.tmp");
	else
		Session::GetInstance("sdTrials.xml", "result.tmp");
	

	CDStartState * cdss = CDStartState::GetInstance(cdg);
	cdss->activate();

	ctrl->run();

	return 0;
}

