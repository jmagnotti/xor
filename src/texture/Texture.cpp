#include "Texture.h"


namespace XOR {

/**
 * Explicit Constructor
 */
Texture::Texture(const char *fileName)
{
	_path = fileName;
	loadFromFile();
}

Texture::Texture(char * data, int size)
{
	loadRwops(data, size);
}


/*
 * height in pixels
 */
int Texture::getHeight()
{
    return _height;
}


/*
 * pointer to the texture
 */
GLuint Texture::getID()
{
    return _id;
}


/*
 * path to the texture file
 */
const char * Texture::getPath()
{ 
    return _path;
}


/*
 * width in pixels
 */
int	Texture::getWidth()
{
    return _width;
}


/*
 * regen the texture after a reshape
 */
void Texture::regenerate()
{
    loadFromFile();
}

/**
 * Load using SDL RWops
 */
void Texture::loadRwops(char * data, int size)
{
	
    // use SDL IMG library to load
    SDL_Surface * texture = NULL;
	SDL_RWops * rw = SDL_RWFromMem(data, size);
	texture = IMG_Load_RW(rw, 1);

    if (texture == NULL) cout << IMG_GetError() << endl;

    else {
		buildTexture(texture);
	}
}

	
/*
 * loads a texture file
 */
void Texture::loadFromFile()
{
    // use SDL IMG library to load
    SDL_Surface * texture = NULL;
    texture = IMG_Load(_path);

    if (texture == NULL) cout << IMG_GetError() << endl;

    else {
		buildTexture(texture);
    }
}

/**
 * Does the GL/SDL dirtwork for building a texture
 */
void Texture::buildTexture(SDL_Surface * texture)
{
	//if (SDL_MUSTLOCK(texture)) SDL_LockSurface(texture);
	glEnable(GL_TEXTURE_2D);
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

     _width  = texture->w;
     _height = texture->h;

     if (texture->format->BytesPerPixel == 4) {
        //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels);
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, texture->w, texture->h, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels );
	 }
	 else {
		 //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->w, texture->h, 0,
				GL_RGB, GL_UNSIGNED_BYTE, texture->pixels);
	 }
	 //if (SDL_MUSTLOCK(texture)) SDL_UnlockSurface(texture);
	 SDL_FreeSurface(texture);
}


/**
 * Binds the texture
 */
void Texture::setActive()
{
#ifdef DEBUG
	cout << "Binding texture: " << getPath() << endl;
#endif
	glBindTexture(GL_TEXTURE_2D, _id);
}

/*
 * glDisable
 */
void Texture::DisableTextures()
{
    glDisable(GL_TEXTURE_2D);
}

/*
 * glEnable
 */
void Texture::EnableTextures()
{
    glEnable(GL_TEXTURE_2D);
}

}

