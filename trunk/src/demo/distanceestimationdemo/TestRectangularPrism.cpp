#include "../../xor.h"

using namespace XOR;
using namespace std;

class HackRP : public RectangularPrism
{
	public: 
	HackRP(Vector3D * point, Dimension3D * size, Paint * paint)
		: RectangularPrism(point, size, paint)
	{}

	RectangularVolume * getVolume()
	{
		return _volume;
	}
};


int main()
{
    HackRP * rp = new HackRP(new Vector3D(-15,-4, 4), new Dimension3D(30, 20, -100), new Paint(Color::WHITE));

	RectangularVolume * rv = rp->getVolume();;

	Vector3D * testPosition = new Vector3D(0,0,0);
	bool truth = false;

	//for (int x=-30; x<30; x++) {
		//testPosition->setPosition(Vector3D::X, x);
		//for (int y=-30; y<30; y++) {
			//testPosition->setPosition(Vector3D::Y, y);
			for (int z = -200; z<10; z++) {
				if (z == -96 || z == 5) truth = !truth; //cout << "SWITCH" << endl;

			   	testPosition->setPosition(Vector3D::Z, z);
				cout <<  //testPosition->toString() << " " <<
					(rv->contains(new Containment(), testPosition) == truth ? "S" : "F");
			}
		   cout	<< endl;
		//}
	//}

	return 0;
}
