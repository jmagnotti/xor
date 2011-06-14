#ifndef CDSECONDDISPLAY_H
#define CDSECONDDISPLAY_H

#include <vector>
#include "CDState.h"
#include "CDGrid.h"

#include "CDChoiceState.h"
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

	void handleTick();

	void handleMouseEvent(MouseEvent * me);

	void handleKeyEvent(KeyEvent * ke);

private:

	CDSecondDisplay();

	int _reactionTime;
	int ticksRemaining;

	bool _handled;

	static CDSecondDisplay * _state;
};

#endif			//CDSECONDDISPLAY_H

