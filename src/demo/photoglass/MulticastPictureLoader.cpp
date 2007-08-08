#include "PictureLoader.h"
#include <vector>
#include <iostream>
#include <string>

using namespace XOR;
using namespace std;

MulticastPictureLoader::MulticastPictureLoader()
{
	_mds = new MulticastDataSocket();
}


vector<Picture*> MulticastPictureLoader::load()
{
	vector<Picture*> pictures;

	readHeader();
	for(int i = 0; i < _numpics; i++) {
		cout << "Reading picture " << i << "." << endl;
		pictures.push_back(readPicture());
	}

	return pictures;
}

/**
 * The header is luckily really one packet with
 * no special markings.  It's simply the number
 * of pictures that are about to be sent.
 */

void MulticastPictureLoader::readHeader()
{
	// there's plenty of growing room here
	// for more complicated packets
	string packet;
	
	packet = _mds->receive();
	
	_numpics = atoi(packet.c_str());	
}

/**
 * Reads the next complete picture from the socket.
 * Pictures are preceeded by a packet which indicates
 * the picture's name, and size. We'll create a buffer
 * that is the picture's size and read that number 
 * of bytes from the socket.
 */
Picture * MulticastPictureLoader::readPicture()
{
	int length    = 0; // size of this picture
	int totalread = 0; // bytes read so far
	string name; // pic's name
	Picture * picture;  // our eventual picture

	char * data; 

	name = _mds->receive();
	cout << "Getting \"" << name << "\"" << endl;
	length = atoi(_mds->receive().c_str());

	// allocate some memory
	data = new char[length];

	while(totalread < length) {
		char * packet;
		int read;
		
		// read the next packet		
		packet = _mds->receiveBytes();
		read = _mds->getBytesRead();

		//copy it into our buffer
		for(int i = 0; i < read; i++) 
			data[i + totalread] = packet[i];
		
		totalread += read;
	}	

	// okay now that we've loaded all of our bytes and fun
	// we can actually make a picture out of it.
	
	TextureFactory * tf = TextureFactory::GetInstance();
	cout << name << endl;
	Paint * p = new Paint(tf->createTextureFromMem(data, length, name.c_str()));
	Transformable3D * cube = new Transformable3D(new Cube(new Vector3D(0.0f, 0.0f, -1.0f ), 1.0f, p));
	picture = new Picture(cube);

	delete [] data;

	return picture;
}

