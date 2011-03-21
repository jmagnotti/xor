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

Texture::~Texture()
{
	glDeleteTextures(1, &_id);
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
	texture = IMG_Load_RW(rw, 0);

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
void Texture::buildTexture(SDL_Surface * surface)
{
    int w, h;
    SDL_Surface *image;
    SDL_Rect area;
    Uint32 saved_flags;
    Uint8 saved_alpha;
	
    /* Use the surface width and height expanded to powers of 2 */
    w = (surface->w);
    h = (surface->h);
	
    image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN     /* OpenGL RGBA masks */
                                 0x000000FF,
                                 0x0000FF00, 0x00FF0000, 0xFF000000
#else
                                 0xFF000000,
                                 0x00FF0000, 0x0000FF00, 0x000000FF
#endif
								 );

    /* Save the alpha blending attributes */
    saved_flags = surface->flags & (SDL_SRCALPHA | SDL_RLEACCELOK);
    SDL_GetSurfaceAlphaMod(surface, &saved_alpha);
    if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA) {
        SDL_SetAlpha(surface, 0, 0);
    }
	
    /* Copy the surface into the GL texture image */
    area.x = 0;
    area.y = 0;
    area.w = surface->w;
    area.h = surface->h;
    SDL_BlitSurface(surface, &area, image, &area);
	
    /* Restore the alpha blending attributes */
    if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA) {
        SDL_SetAlpha(surface, saved_flags, saved_alpha);
    }
	
    /* Create an OpenGL texture for the image */
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
    SDL_FreeSurface(image);     /* No longer needed */
     _width  = surface->w;
     _height = surface->h;

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

