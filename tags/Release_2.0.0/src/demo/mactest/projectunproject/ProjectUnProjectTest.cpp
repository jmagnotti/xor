#include "../../../xor.h"
#include <iostream>
#include <string>

using namespace std;
using namespace XOR;


class ProjectUnProjectTest : public TimerListener
{

public:

    ProjectUnProjectTest()
    {
        Controller * c = Controller::GetInstance(NULL);

        if (c != NULL)
            c->getTimer()->addListener(this);
        else
            cout << "CONTROLLER NOT INTIIALIZED" << endl;
    }

    /**
     * returns if the two vectors are equal
     */
    bool areEqual(Vector3D * a, Vector3D * b)
    {
        GraphicsConversionUtility * gcu = GraphicsConversionUtility::GetInstance();
        bool equal = true;
        int i = 0;

        while (equal && i < 3) {
            equal = gcu->compare_f(a->get(i), b->get(i), 1.0f);
            ++i;
        }

        return equal;
    }


    /**
     * Coordinate mapping test
     */
    void runTest()
    {
        Viewer * viewer = Controller::GetInstance(NULL)->getViewer();

        map<Vector3D*, Vector3D*> screenToWorld;

        Vector3D * current;

        const int WIDTH = 1280;
        const int HEIGHT = 1024;

        for(int i=0; i<WIDTH; i++) {
            for(int j=0; j<HEIGHT; j++) {
                current = new Vector3D(i, j, 0);
                screenToWorld[current] = viewer->toWorldCoordinates(current);
            }
        }
                
        map<Vector3D*,Vector3D*>::iterator iter = screenToWorld.begin();
        map<Vector3D*,Vector3D*>::iterator end = screenToWorld.end();

        Vector3D * screenCoord;
        int failures = 0;

        while (iter != end) {
            screenCoord = viewer->toScreenCoordinates(iter->second);

            if (! areEqual(screenCoord, iter->first))
                failures++;
                
            ++iter;
        }

        const int TRIALS = WIDTH * HEIGHT; 

        cout << "Failed " << failures << " out of " << TRIALS << " possible." << endl;
        float percent = 100* ((TRIALS - failures) / TRIALS); 
        cout << "Success Rate: " << percent << "%" << endl;
    
        Controller::GetInstance(NULL)->getModel()->addObject("msg", new String2D("Complete!", 300, 350, Color::GREEN));

        screenToWorld.clear();
    }


    void handleTick()
    {
        const long LONG_TIME = 9999999;

        cout << "---Viewer Unit Test---" << endl;
        cout << "Slowing Timer way down" << endl;

        long interval = Controller::GetInstance(NULL)->getTimer()->getInterval();

        Controller::GetInstance(NULL)->getTimer()->SetInterval(LONG_TIME);

        runTest();

        Controller::GetInstance(NULL)->getTimer()->removeListener(this);

        Controller::GetInstance(NULL)->getTimer()->SetInterval(interval);
    }

};

class VoidObject : public Object3D
{
    Vector3D * getBaseVector(){}
    Dimension3D * getDimension(){}
    void renderObject() {}
};

int main(int argc, char * argv[])
{
    Controller * ctrl = Controller::GetInstance(InputEventProxyFactory::GetInstance());
    ctrl->defaultConfiguration();

    new ProjectUnProjectTest();

    ctrl->setModel(new String2D("Project UnProject Test", 300, 300, Color::RED));

    ctrl->getKeyboard()->addListener(new DefaultKeyboardListener());

    ctrl->run();

    return 0;
}





