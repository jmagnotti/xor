#ifndef PRINTACTION_H
#define PRINTACTION_H

#include <iostream>
#include "../../xor.h"
#include "CDSecondDisplay.h"

using namespace XOR;

/**
 *
 */
class PrintAction : public Action
{

public:

    
    PrintAction(int x);

    void execute();

private:
	int  _x;
	int  _y;

    PrintAction();
};


#endif			// PRINTACTION_H

