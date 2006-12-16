#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>

using namespace std;

namespace XOR {

class Texture
{

protected:
//	_AUX_RGBImageRec * _image;

	char* _path;
	int _height, _width;
	unsigned int _id;
	void loadFromFile();	//this is the preferred method to use for creation

public:
	
	//--for legacy support
	Texture(){}	
	void loadFromFile(char *filename);
	//--

	/**
	 * Explicit Constructor
	 */
	Texture(char *fileName);


	void setActive();

	//--GETTERS--//
	int				getHeight();
	unsigned int	getID();
	char*			getPath();
	int				getWidth();

};

}

#endif			//TEXTURES_H
