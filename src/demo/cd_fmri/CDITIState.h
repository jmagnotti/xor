#ifndef CDITISTATE_H
#define CDITISTATE_H

#include "CDState.h"
#include "CDFixateState.h"
#include "CDClosingState.h"
#include "Session.h"

using namespace std;

class CDITIState : public CDState 
{

public:

	static CDITIState * GetInstance(CDGrid * grid);

	void handleTick();

	void activate();

private:

	CDITIState();

    int ticksRemaining;

	static CDITIState * _state;
};

#endif			//CDFLICKERDISPLAY_H

