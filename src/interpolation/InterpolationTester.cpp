#include "../core/Controller.h"
#include "Interpolator.h"
#include "../shape/Point3D.h"
#include "InterpolationListener.h"
#include "../shape/String2D.h"
#include "../shape/Cube.h"


namespace XOR {

/**
 * Tests the interpolation.
 */
class InterpolationTester : public InterpolationListener
{


public: 

    Point3D *start, *end;
    static const int TEN_SECONDS = 10000;
    unsigned int time;
    

    /*
     * Constructors
     */
    InterpolationTester()
    {
    	
    }


    /*
     *  Called when the interpolation is finished
     */
    void interpolationComplete()
    {
        cout << "Finished!" << endl;
    }



};


/**
 *  Tester Main
 */
int main(int argc, char **argv)
{
    cout << "Not implemented" << endl;
}

}


