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

	void handleKeyEvent(KeyEvent * ke);

	void activate();

private:

	CDStartState(){}

	static CDStartState * _state;

};

#endif			//CDSTARTSTATE_H

