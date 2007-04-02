#ifndef TEXTURE_H
#define TEXTURE_H


#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_opengl.h>


using namespace std;

namespace XOR {

class Texture
{


public:
	
	/**
	 * Explicit Constructor
	 */
	Texture(const char * fileName);


    /*
     *
     */
	void setActive();


    /*
     * enables texturing if they are not already enabled
     */
    static void EnableTextures();


    /*
     * disables the textures if they are not already disabled
     */
    static void DisableTextures();


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
	const char * getPath();


    /*
     */
	int	getWidth();

    
    /**
     * Rebuilds the texture.
     */
    void regenerate();


private:

    Texture();

	const char * _path;

	int _height, _width;

	GLuint _id;

	void loadFromFile();

};

}

#endif			//TEXTURES_H
