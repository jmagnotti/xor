#ifndef CDSTARTSTATE_H
#define CDSTARTSTATE_H

#include "CDState.h"
#include "CDFixateState.h"

#include <SDL/SDL.h>

class CDFixateSearch;

using namespace XOR;


class CDStartState : public CDState 
{
public:

	static CDStartState * GetInstance(CDGrid * grid);

	void handleMouseEvent(MouseEvent * me);

	void activate();

private:

	Rectangle2D * _instructions;

	static CDStartState * _state;

	CDStartState();
};


class StartFixation : public XOR::Action
{

public:

	StartFixation(CDGrid * grid);
	void execute();

private:

	CDGrid * _grid;

};

#endif			//CDSTARTSTATE_H

