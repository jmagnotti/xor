#ifndef CDINITIALDISPLAY_H
#define CDINITIALDISPLAY_H

#include <vector>
#include "CDState.h"
#include "CDGrid.h"

#include "CDRetentionInterval.h"
#include "Helper.h"
#include "Session.h"


using namespace std;

class CDInitialDisplay : public CDState 
{

public:

	static CDInitialDisplay * GetInstance(CDGrid * grid);

	void handleTick();

	void activate();

private:

    int ticksRemaining;

	CDInitialDisplay();
	static CDInitialDisplay * _state;
};

#endif			//CDINITIALDISPLAY_H

