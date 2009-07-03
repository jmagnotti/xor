#ifndef CDFIXATESTATE_H
#define CDFIXATESTATE_H

#include <vector>
#include "CDState.h"
#include "CDInitialDisplay.h"

using namespace std;

class CDInitialDisplay;

class CDFixateState : public CDState 
{

public:

	static CDFixateState * GetInstance(CDGrid * grid);

	void handleTick();

	void activate();

private:

	CDFixateState();
	vector<int> _positions;

	static CDFixateState * _state;
};

#endif			//CDFIXATESTATE_H

