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

XMLPictureLoader::XMLPictureLoader(char * file)
{
	_file = file;		
}
vector<Picture*> XMLPictureLoader::load()
{
	vector<Picture*> pictures; // what we'll be sending back

	XMLNode xDemoNode  = XMLNode::openFileHelper(_file, "demo");
	// default to the first album in the file
	XMLNode xAlbumNode = xDemoNode.getChildNode("albums").getChildNode("album");
	
	// xmlParser uses this for some crap
	int cubeIterator = 0;
	int numCubes = xAlbumNode.nChildNode("cube");
	for(int i = 0; i < numCubes; i++) {
		int faceIterator = 0;
		int faceCount = 0;
		XMLNode xCubeNode = xAlbumNode.getChildNode("cube", &cubeIterator);

		faceCount = xCubeNode.nChildNode("face");
		for(int j = 0; j < faceCount; j++) {
			XMLNode xFaceNode = xCubeNode.getChildNode("face", &faceIterator);
			if(j == 0) {
				Transformable3D * cube = loadCube(xFaceNode.getAttribute("image"));
				pictures.push_back(new Picture(cube));
			}
		}
	}

	return pictures;
}

Transformable3D * XMLPictureLoader::loadCube(const char * path) 
{
	
	TextureFactory * tf = TextureFactory::GetInstance();
	Paint * p = new Paint(tf->createTexture(path));
	Transformable3D * cube = new Transformable3D(new Cube(new Vector3D(0.0f, 0.0f, -1.0f ), 1.0f, p));
	return cube;
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
