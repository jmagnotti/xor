#ifndef CDCLOSINGSTATE_H
#define CDCLOSINGSTATE_H

#include <SDL/SDL.h>
#include "CDState.h"

using namespace XOR;


class CDClosingState : public CDState 
{
public:

	static CDClosingState * GetInstance(CDGrid * grid);

	void activate();

private:

	Rectangle2D * _instructions;

	static CDClosingState * _state;

	CDClosingState();
};

#endif			//CDCLOSINGSTATE_H

