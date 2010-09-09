#ifndef CDSECONDDISPLAY_H
#define CDSECONDDISPLAY_H

#include <vector>
#include "CDState.h"
#include "CDGrid.h"

#include "CDITIState.h"
#include "Helper.h"
#include "Session.h"

using namespace std;

class CDSecondDisplay : public CDState 
{

public:

	static CDSecondDisplay * GetInstance(CDGrid * grid);

	/*
	 * doesn't change the grid
	 */
	static CDSecondDisplay * GetInstance();

	void activate();

	void handleChoice(int location);

	void handleMouseEvent(MouseEvent * me);

private:

	CDSecondDisplay();

	int _reactionTime;

	static CDSecondDisplay * _state;
};

#endif			//CDSECONDDISPLAY_H

