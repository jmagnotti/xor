#ifndef CDDECIDESTATE_H
#define CDDECIDESTATE_H

#include <vector>
#include "CDState.h"
#include "CDGrid.h"

#include "CDITIState.h"
#include "Helper.h"
#include "Session.h"

using namespace std;

class CDChoiceState : public CDState 
{

public:

	static CDChoiceState * GetInstance(CDGrid * grid);

	/*
	 * doesn't change the grid
	 */
	static CDChoiceState * GetInstance();

	void activate();

	void handleChoice(int location);

	void handleTick();

	//void handleMouseEvent(MouseEvent * me);

	void handleKeyEvent(KeyEvent * ke);

private:

	CDChoiceState();

	int _reactionTime;
	int ticksRemaining;

	bool _handled;

	static CDChoiceState * _state;

    Rectangle2D * _instructions;
};

#endif			//CDDECIDESTATE_H

