#ifndef CDFLICKERDISPLAY_H
#define CDFLICKERDISPLAY_H

#include <vector>
#include "CDState.h"

#include "CDSecondDisplay.h"

using namespace std;

class CDFlickerDisplay : public CDState 
{

public:

	static CDFlickerDisplay * GetInstance(CDGrid * grid);

	void handleTick();

	void activate();

private:

	CDFlickerDisplay();

	static CDFlickerDisplay * _state;
};

#endif			//CDFLICKERDISPLAY_H

