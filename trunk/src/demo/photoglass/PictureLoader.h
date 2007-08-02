#ifndef PICTURELOADER_H
#define PICTURELOADER_H

#include "../../xor.h"
#include "Arrangement.h"
#include "Picture.h"
#include "xmlParser/xmlParser.h"
#include <iostream>
#include <vector>

using namespace XOR;
using namespace std;

class PictureLoader
{

public:
	/**
	 * Loads pictures somehow, who cares
	 */
	virtual vector<Picture*> load();

};

class MulticastPictureLoader : public PictureLoader
{

public:
	/**
	 * Loads pictures somehow, who cares
	 */
	virtual vector<Picture*> load();
};

class XMLPictureLoader : public PictureLoader
{
	public:
		XMLPictureLoader(char * file);
		virtual vector<Picture*> load();
	private:
		char * _file;
		Transformable3D * loadCube(const char * path);
};

class FakePictureLoader : public PictureLoader
{
	public:
		// pass in the number of monkies
		FakePictureLoader(int num);
		virtual vector<Picture*> load();
	private:
		int numMonks; 
};

#endif			// PICTURELOADER_H
