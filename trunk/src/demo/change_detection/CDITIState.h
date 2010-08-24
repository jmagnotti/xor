#ifndef CDITISTATE_H
#define CDITISTATE_H

#include "CDState.h"
#include "CDFixateState.h"
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

	static CDITIState * _state;
};

#endif			//CDFLICKERDISPLAY_H

