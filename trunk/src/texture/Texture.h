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

	Texture(char * data, int size);

	virtual ~Texture();

    /**
     * Makes this texture the currently activated texture. This should not
	 * be called by a user application, but rather is used by the
	 * framework to ensure the appropriate texture is applied to a given
	 * object.
     */
	void setActive();

    /**
     * Enables texturing. If called during the rendering loop (dont do
	 * this unless you are sure of the rendering order) only texels applied
	 * after this call will appear. 
	 *
	 * The framework _never_ calls this function, so if you have previously
	 * called DisableTextures(), you must explicity re-enable them.
     */
    static void EnableTextures();

    /**
     * Disables texturing. If called during the rendering loop (dont do
	 * this unless you are sure of the rendering order) only texels applied
	 * before this call will appear. 
	 *
	 * The framework _never_ calls this function, so if you have previously
	 * called EnableTextures(), you must explicity re-disable them.
     */
    static void DisableTextures();

    /**
     * Returns the height, in pixels, of the texture object. Note that this has
     * nothing to do with the final rendered version, only the image as it was
     * read from the file.
     */
	int getHeight();

    /*
	 * The id of the texture, as assigned by OpenGL.
     */
	GLuint getID();

    /**
	 * The path to the texture. Note that this is not guaranteed to exist,
	 * it merely mimicks whatever was passed in.
     */
	const char * getPath();

    /**
     * Returns the width, in pixels, of the texture object. Note that this has
     * nothing to do with the final rendered version, only the image as it was
     * read from the file.
     */
	int	getWidth();
    
    /**
     * Rebuilds the texture.
     */
    void regenerate();

private:

    Texture();

	/**
	 * Reads the file from disk using the given path.
	 */
	void loadFromFile();
	void loadRwops(char * data, int size);
	void buildTexture(SDL_Surface * texture); 

	const char * _path;

	int _height, _width;

	GLuint _id;


};

}

#endif			//TEXTURES_H

