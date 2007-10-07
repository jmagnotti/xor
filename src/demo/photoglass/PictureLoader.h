#ifndef PICTURELOADER_H
#define PICTURELOADER_H

#include "../../xor.h"
#include "Arrangement.h"
#include "Picture.h"
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
	virtual vector<Picture*> load()=0;

};

class MulticastPictureLoader : public PictureLoader
{

public:
	MulticastPictureLoader();
	/**
	 * Loads pictures from a Multicast Socket 
	 */
	vector<Picture*> load();

private:
	MulticastDataSocket * _mds;
	/** 
	 * A couple of helper functions. Docs in cpp file
	 */
	void readHeader(); // reads first packet
	Picture * readPicture();

	

	int _numpics; // number of pics we'll receive

};

class XMLPictureLoader : public PictureLoader
{
	public:
		XMLPictureLoader(char * file);
		vector<Picture*> load();

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
