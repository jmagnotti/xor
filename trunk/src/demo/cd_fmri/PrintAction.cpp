#include "PrintAction.h"

PrintAction::PrintAction()
{}


PrintAction::PrintAction(int x)
{
    _x = x;
    //_y = y;
}

void PrintAction::execute()
{
	CDSecondDisplay::GetInstance()->handleChoice(_x);
    //cout << "Action fired @: " << _x << endl;
}
  
