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
    Controller * ctrl = Controller::GetInstance();//(new XavierConfiguration());
    //ctrl->defaultConfiguration();
    ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());
    
    Vector2D * gridOrigin = new Vector2D(500,500);
    Dimension2D * gridSize = new Dimension2D(200,50);

    PrintAction * pa;    
    pa = new PrintAction(100,100);

    new PrintMousePosition(ctrl);
   
    Dimension2D * iconSize;
    iconSize = new Dimension2D(50,50);

    Icon2D * icon;
    icon = new Icon2D(gridOrigin, iconSize, "./images/x_red.png");

    ActionItem * ai;
    ai = new ActionItem(icon, pa);
 
    HotspotGrid * hsg = new HotspotGrid(gridOrigin, gridSize);

    hsg->addAction(ai);
    
    icon = new Icon2D(hsg->getNextLocation(), iconSize, "./images/y_green.png");
   
    ai = new ActionItem(icon, pa);

    hsg->addAction(ai);    

    icon = new Icon2D(hsg->getNextLocation(), iconSize, "./images/z_blue.png");
   
    ai = new ActionItem(icon, pa);
    hsg->addAction(ai);    
    
    icon = new Icon2D(hsg->getNextLocation(), iconSize, "./images/white.png");
   
    ai = new ActionItem(icon, pa);
    hsg->addAction(ai);    

    ctrl->getMouse()->addListener(hsg);

    ctrl->setModel(hsg);

    ctrl->run();


    return 0;
}
