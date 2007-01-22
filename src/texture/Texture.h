#ifndef TEXTURE_H
#define TEXTURE_H


#include <iostream>
#include "../../include/SDL.h"
#include "../../include/SDL_image.h"
#include "../../include/SDL_opengl.h"


using namespace std;

namespace XOR {

class Texture
{


public:
	
	/**
	 * Explicit Constructor
	 */
	Texture(char * fileName);


    /*
     *
     */
	void setActive();


    /*
     * Returns the height, in pixels, of the texture object. Note that this has
     * nothing to do with the final rendered version, only the image as it was
     * read from the file.
     */
	int getHeight();


    /*
     */
	GLuint getID();


    /*
     */
	char * getPath();


    /*
     */
	int	getWidth();


private:

    Texture();

	char* _path;
	int _height, _width;
	GLuint _id;
	void loadFromFile();	//this is the preferred method to use for creation

};

}

#endif			//TEXTURES_H
