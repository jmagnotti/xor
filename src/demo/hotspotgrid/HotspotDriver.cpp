#include "../../xor.h"
#include "PrintMousePosition.h"
#include "HotspotGrid.h"
#include "PrintAction.h"
#include "ActionItem.h"
#include "Icon2D.h"

using namespace XOR;
using namespace std;

int main(int argc, char * argv[])
{
    Controller * ctrl = Controller::GetInstance();
    ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
    
    Vector2D * gridOrigin = new Vector2D(100,100);
    Dimension2D * gridSize = new Dimension2D(500,500);

    PrintAction * pa;    
    pa = new PrintAction(100,100);

    new PrintMousePosition(ctrl);
   
    Dimension2D * iconSize;
    iconSize = new Dimension2D(100,100);

    Icon2D * icon;
    icon = new Icon2D(gridOrigin, iconSize, "aquab.bmp");

    ActionItem * ai;
    ai = new ActionItem(icon, pa);
 
    HotspotGrid * hsg = new HotspotGrid(gridOrigin, gridSize);

    if (hsg->addAction(ai))
		cout << "SUCCESS" << endl;
    
    icon = new Icon2D(hsg->getNextLocation(), iconSize, "aquab.bmp");
    ai = new ActionItem(icon, pa);
    hsg->addAction(ai);    

    icon = new Icon2D(hsg->getNextLocation(), iconSize, "aquab.bmp");
    ai = new ActionItem(icon, pa);
    hsg->addAction(ai);    
    
    icon = new Icon2D(hsg->getNextLocation(), iconSize, "aquab.bmp");
    ai = new ActionItem(icon, pa);
    hsg->addAction(ai);    

    ctrl->getMouse()->addListener(hsg);

    ctrl->setModel(hsg);

    ctrl->run();


    return 0;
}
