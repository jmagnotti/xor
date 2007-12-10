#ifndef PRINTACTION_H
#define PRINTACTION_H

#include "../../xor.h"

using namespace XOR;

/**
 *
 */
class PrintAction : public Action
{

public:

    
    PrintAction(int x, int y);

    void execute();

private:
	int  _x;
	int  _y;

    PrintAction();
};


#endif			// PRINTACTION_H

