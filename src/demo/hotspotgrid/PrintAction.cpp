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
    cout << "Action fired @: " << _x << endl;
}
  
