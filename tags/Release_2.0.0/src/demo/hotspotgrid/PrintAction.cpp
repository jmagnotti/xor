#include "PrintAction.h"

PrintAction::PrintAction()
{}


PrintAction::PrintAction(int x, int y)
{
    _x = x;
    _y = y;
}

void PrintAction::performAction()
{
    cout << "Action fired @: " << _x << ", " << _y << endl;
}
  