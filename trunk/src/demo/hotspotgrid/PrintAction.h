#ifndef PRINTACTION_H
#define PRINTACTION_H

#include "Action.h"
#include <iostream>

using namespace std;
using namespace XOR;

/**
 *
 */
class PrintAction : public Action
{

public:

    
    PrintAction(int x, int y);

    void performAction();

private:
	int  _x;
	int  _y;

    PrintAction();
};


#endif			// PRINTACTION_H

