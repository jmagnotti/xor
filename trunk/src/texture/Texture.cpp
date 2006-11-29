#include "Texture.h"


/**
 * Explicit Constructor
 */
Texture::Texture(char *fileName)
{
	_path = fileName;
	loadFromFile();
}


//--GETTERS--//
int				Texture::getHeight()	{ return _height;	}
unsigned int	Texture::getID()		{ return _id;		}
char*			Texture::getPath()	{ return _path;		}
int				Texture::getWidth()	{ return _width;		}

	
/*
 * loads a bmp texture file
 */
void Texture::loadFromFile()
{
	return;

//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glGenTextures(1, &_id); 
//	glBindTexture(GL_TEXTURE_2D, _id);

//	_image = auxDIBImageLoadA( (const char*) _path );

//	_height = _image->sizeY;
//	_width = _image->sizeX;

	//gluBuild2DMipmaps(	GL_TEXTURE_2D, 3, _width, _height, GL_RGB,
//						GL_UNSIGNED_BYTE,
//						_image->data);
//	delete _image;
}

/* 
 * get the texture data from the file
 */
void Texture::loadFromFile(char * filename)
{
	return;
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//	glGenTextures(1, &_id); 
//	glBindTexture(GL_TEXTURE_2D, _id);
/**
	_image = auxDIBImageLoadA( (const char*) filename );

	_height = _image->sizeY;
	_width = _image->sizeX;

	gluBuild2DMipmaps(	GL_TEXTURE_2D, 3, _width, _height,	GL_RGB,
						GL_UNSIGNED_BYTE,
						_image->data);
	delete _image;
*/
}

/**
 * Binds the texture
 */
void Texture::setActive()
{
//	glBindTexture(GL_TEXTURE_2D, _id);
}
