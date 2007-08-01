#include "PictureLoader.h"
#include <vector>
#include <iostream>

using namespace XOR;
using namespace std;

vector<Picture*> PictureLoader::load()
{
	vector<Picture*> somepics;
	return somepics;
}

FakePictureLoader::FakePictureLoader(int num)
{
	numMonks = num;
}

vector<Picture*> FakePictureLoader::load()
{
	vector<Picture*> fakepics;
	TextureFactory * tf = TextureFactory::GetInstance();
	Paint * p = new Paint(tf->createTexture("monkey.png"));
	for(int i = 0; i < numMonks; i++) {
		cout << "Loading monkey " << i << "." << endl;
		Picture * pic;
		Transformable3D * cube = new Transformable3D(new Cube(new Vector3D(0.0f, 0.0f, -1.0f ), 1.0f, p));
		pic = new Picture(cube);
		fakepics.push_back(pic);
	}

	return fakepics;
}
