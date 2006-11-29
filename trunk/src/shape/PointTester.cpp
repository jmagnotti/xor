/**
 * why won't Point3D compile?
 */

#include <iostream>
#include "Point3D.h"

using namespace std;
using XOR::Point3D;

int main()
{
    Point3D * p = new Point3D();
    delete p;

    cout << "Hooray" << endl;
    
    return 0;
}
