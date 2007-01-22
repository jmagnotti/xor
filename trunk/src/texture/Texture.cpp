#include "Texture.h"


namespace XOR {

/**
 * Explicit Constructor
 */
Texture::Texture(char *fileName)
{
	_path = fileName;
	loadFromFile();
}


int Texture::getHeight()
{
    return _height;
}


GLuint Texture::getID()
{
    return _id;
}


char * Texture::getPath()
{ 
    return _path;
}


int	Texture::getWidth()
{
    return _width;
}

	
/*
 * loads a bmp texture file
 */
void Texture::loadFromFile()
{
    // use SDL IMG library to load
    SDL_Surface * texture = IMG_Load(_path);
    glGenTextures(1, &_id);
   // glBindTexture(GL_TEXTURE_2D);

	_width  = texture->w;
	_height = texture->h;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, texture->pixels);

    //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, _width, _height, GL_RGB,
    //GL_UNSIGNED_BYTE, _image->data);

    SDL_FreeSurface(texture);
}

/**
 * Binds the texture
 */
void Texture::setActive()
{
	glBindTexture(GL_TEXTURE_2D, _id);
}

}
